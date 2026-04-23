import os
import subprocess
import time
import re
import math
import glob

# CONFIG
EXECUTABLE = "zadanie2.exe"
TIMEOUT_SECONDS = 30 * 60  # 30 min tak na wszelki wypadek (chociaż usunąłem z subprocess)

def nint(x):
    return int(x + 0.5)

def update_config(algorithm, upper_bound_method, generate_symmetric, tsp_file):
    lines = []
    with open("config.txt", "r") as f:
        lines = f.readlines()
        
    with open("config.txt", "w") as f:
        for line in lines:
            if line.startswith("ALGORITHM="):
                f.write(f"ALGORITHM={algorithm}\n")
            elif line.startswith("UPPER_BOUND_METHOD="):
                f.write(f"UPPER_BOUND_METHOD={upper_bound_method}\n")
            elif line.startswith("GENERATE_NEW="):
                f.write(f"GENERATE_NEW=0\n")
            elif line.startswith("GENERATE_SYMMETRIC="):
                f.write(f"GENERATE_SYMMETRIC={generate_symmetric}\n")
            elif line.startswith("TSP_FILE="):
                f.write(f"TSP_FILE={tsp_file}\n")
            elif line.startswith("SHOW_PROGRESS="):
                f.write(f"SHOW_PROGRESS=0\n")
            else:
                f.write(line)

def run_test_case(algorithm, ub_method, symmetric, filepath, instance_name):
    # Aktualizacja config.txt pod nowy parser wypluty do temp
    update_config(algorithm, ub_method, 1 if symmetric else 0, filepath)
    
    out_file = f"temp_out_tsplib_{algorithm}_{ub_method}_{instance_name}.txt"
    cmd = f'cmd.exe /c "start /B /wait /affinity 1 {EXECUTABLE} > {out_file}"'
    
    try:
        subprocess.run(cmd, shell=True) # Brak limitu czasu
        
        with open(out_file, "r") as f:
            output = f.read()
            
        cost_match = re.search(r"Najlepszy znaleziony koszt: (\d+)", output)
        time_match = re.search(r"Sredni czas wykonania.*?: ([\d\.]+) \[ms\]", output)
        mem_match = re.search(r"Szczytowe zuzycie pamieci: (\d+) KB", output)
        
        cost = cost_match.group(1) if cost_match else "ERROR"
        time_ms = time_match.group(1) if time_match else "ERROR"
        mem_kb = mem_match.group(1) if mem_match else "ERROR"
        
        if os.path.exists(out_file):
            os.remove(out_file)
            
        return cost, time_ms, mem_kb, "OK"
        
    except Exception as e:
        os.system("taskkill /f /im zadanie2.exe >nul 2>&1")
        time.sleep(1)
        return "-", "-", "-", f"ERROR: {str(e)}"

# -------- PARSERY --------
def parse_tsplib(filepath):
    lines = []
    with open(filepath, "r") as f:
        for line in f:
            line = line.strip()
            if line and line != "EOF":
                lines.append(line)
                
    meta = {}
    idx = 0
    while idx < len(lines):
        line = lines[idx]
        if ":" in line:
            parts = line.split(":", 1)
            meta[parts[0].strip()] = parts[1].strip()
            idx += 1
        elif line.startswith("EDGE_WEIGHT_SECTION") or line.startswith("NODE_COORD_SECTION"):
            break
        else:
            idx += 1
            
    n = int(meta.get("DIMENSION", 0))
    is_symmetric = (meta.get("TYPE", "TSP") == "TSP")
    
    matrix = [[0]*n for _ in range(n)]
    
    # Przewijanie do sekcji z danymi
    while idx < len(lines) and not (lines[idx].startswith("EDGE_WEIGHT_SECTION") or lines[idx].startswith("NODE_COORD_SECTION")):
        idx += 1
        
    section_type = lines[idx]
    idx += 1
    data_lines = lines[idx:]
    
    if meta.get("EDGE_WEIGHT_TYPE") == "GEO":
        # Wzór koordynatów GEO z dokumentacji
        coords = []
        for line in data_lines:
            parts = line.split()
            if len(parts) >= 3:
                coords.append((float(parts[1]), float(parts[2])))
        PI = 3.141592
        lat = []
        lon = []
        for (x, y) in coords:
            # Dokumentacja TSPLIB nint(x) i minuty
            deg = nint(x)
            minute = x - deg
            latitude = PI * (deg + 5.0 * minute / 3.0) / 180.0
            lat.append(latitude)
            
            deg = nint(y)
            minute = y - deg
            longitude = PI * (deg + 5.0 * minute / 3.0) / 180.0
            lon.append(longitude)
            
        RRR = 6378.388
        for i in range(n):
            for j in range(n):
                if i == j:
                    matrix[i][j] = -1
                else:
                    q1 = math.cos(lon[i] - lon[j])
                    q2 = math.cos(lat[i] - lat[j])
                    q3 = math.cos(lat[i] + lat[j])
                    val = RRR * math.acos(0.5 * ((1.0 + q1)*q2 - (1.0 - q1)*q3)) + 1.0
                    matrix[i][j] = nint(val) # Zaokraglenie do najblizszego calkowitego zgodnie ze standardem nint() TSPLIB
                    
    elif meta.get("EDGE_WEIGHT_FORMAT") == "FULL_MATRIX":
        nums = []
        for line in data_lines:
            nums.extend([int(x) for x in line.split()])
        num_idx = 0
        for i in range(n):
            for j in range(n):
                if i == j:
                    matrix[i][j] = -1
                else:
                    matrix[i][j] = nums[num_idx]
                num_idx += 1
                
    elif meta.get("EDGE_WEIGHT_FORMAT") == "LOWER_DIAG_ROW":
        nums = []
        for line in data_lines:
            nums.extend([int(x) for x in line.split()])
        num_idx = 0
        for i in range(n):
            for j in range(i+1):
                val = nums[num_idx]
                num_idx += 1
                if i == j:
                    matrix[i][j] = -1
                else:
                    matrix[i][j] = val
                    matrix[j][i] = val
    else:
        print(f"Nieobslugiwany format: {meta.get('EDGE_WEIGHT_TYPE')} / {meta.get('EDGE_WEIGHT_FORMAT')} w {filepath}")
        return None, is_symmetric
        
    return matrix, is_symmetric


if __name__ == "__main__":
    if not os.path.exists("data/TSPLIB"):
        print("Brak folderu data/TSPLIB")
        exit()

    ALGORITHMS = ["BB_DFS_REC", "BB_DFS_STACK", "BB_LC"]
    UB_METHODS = ["NONE"]
    
    with open("results/research_tsplib.csv", "w") as f:
        f.write("Filename,Type,Size,Algorithm,UB_Method,BestCost,TimeMs,PeakMemoryKB,Status\n")
        
    files = glob.glob("data/TSPLIB/**/*.tsp", recursive=True) + glob.glob("data/TSPLIB/**/*.atsp", recursive=True)
    
    print("=== ROZPOCZECIE BADAN TSPLIB ===")
    for filepath in files:
        filename = os.path.basename(filepath)
        print(f"Parsowanie {filename}...")
        
        matrix, is_symmetric = parse_tsplib(filepath)
        if not matrix:
            continue
            
        n = len(matrix)
        type_str = "TSP" if is_symmetric else "ATSP"
        
        # Zapisz przeliczona i plaska macierz zeby program w C++ mial prostą drogę
        temp_parsed_file = "data/python_temp_tsplib.atsp"
        with open(temp_parsed_file, "w") as f:
            f.write(f"{n}\n")
            for row in matrix:
                f.write(" ".join(map(str, row)) + "\n")
                
        for algo in ALGORITHMS:
            for ub in UB_METHODS:
                print(f"[{filename} N={n}] Algo={algo} UB={ub} ...", end=" ", flush=True)
                cost, t, mem, status = run_test_case(algo, ub, is_symmetric, temp_parsed_file, filename.replace(".","_"))
                print(status if status != "OK" else f"{t} ms")
                
                with open("results/research_tsplib.csv", "a") as f:
                    f.write(f"{filename},{type_str},{n},{algo},{ub},{cost},{t},{mem},{status}\n")
