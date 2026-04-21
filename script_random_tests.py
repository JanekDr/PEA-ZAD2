import os
import subprocess
import time
import re
import random

# CONFIG
EXECUTABLE = "zadanie2.exe"
TIMEOUT_SECONDS = 15 * 60  # 15 minutes
DRY_RUN = True # Zmien na False zeby wlaczyc glowne badania

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

def generate_matrix(dimension, symmetric, filename):
    matrix = [[0 for _ in range(dimension)] for _ in range(dimension)]
    for i in range(dimension):
        for j in range(dimension):
            if i == j:
                matrix[i][j] = -1
            elif symmetric and i > j:
                matrix[i][j] = matrix[j][i]
            else:
                matrix[i][j] = random.randint(1, 100)
                
    with open(filename, "w") as f:
        f.write(f"{dimension}\n")
        for row in matrix:
            f.write(" ".join(map(str, row)) + "\n")

def run_test_case(algorithm, ub_method, symmetric, size, instance_id):
    filename = "data/python_temp.atsp"
    
    update_config(algorithm, ub_method, 1 if symmetric else 0, filename)
    
    out_file = "temp_out.txt"
    # Zgodnie z zyczeniem prowadzącego: start /B /wait /affinity 1 ...
    cmd = f'cmd.exe /c "start /B /wait /affinity 1 {EXECUTABLE} > {out_file}"'
    
    try:
        subprocess.run(cmd, shell=True, timeout=TIMEOUT_SECONDS)
        
        with open(out_file, "r") as f:
            output = f.read()
            
        cost_match = re.search(r"Najlepszy znaleziony koszt: (\d+)", output)
        time_match = re.search(r"Sredni czas wykonania.*?: ([\d\.]+) \[ms\]", output)
        mem_match = re.search(r"Szczytowe zuzycie pamieci: (\d+) KB", output)
        
        cost = cost_match.group(1) if cost_match else "ERROR"
        time_ms = time_match.group(1) if time_match else "ERROR"
        mem_kb = mem_match.group(1) if mem_match else "ERROR"
        
        return cost, time_ms, mem_kb, "OK"
        
    except subprocess.TimeoutExpired:
        # Jesli poleci Timeout, trzeba bezwzglednie ubic wywolany proces zadanie2.exe
        os.system("taskkill /f /im zadanie2.exe >nul 2>&1")
        return "-", "-", "-", "TIMEOUT"

def run_dry_run():
    print("=== START DRY RUN (Sprawdzanie maksymalnego rozmiaru) ===")
    print("Sprawdzamy algorytm BB_DFS_REC bez UB (poniewaz on najglebiej szuka i pamieta). Mozemy sprawdzic tez BFS na zacinanie.")
    
    size = 11
    while True:
        print(f"Testowanie rozmiaru N={size} ...", end=" ", flush=True)
        generate_matrix(size, False, "data/python_temp.atsp")
        
        # Badamy DFS bez górnego ograniczenia, by sprawdzic pesymistyczny wariant wejscia w slepe zangazowania
        cost, t, mem, status = run_test_case("BB_DFS_REC", "NONE", False, size, 0)
        
        if status == "TIMEOUT":
            print(f"TIMEOUT! Czas osiagnal {TIMEOUT_SECONDS} sek (15 minut)!")
            break
        elif status == "OK":
            print(f"Wykonano. Czas: {t} ms, Szczytowa Pamiec: {mem} KB")
            size += 1
        else:
            print("BLAD KRYTYCZNY programu. Prawdopodobnie zabraklo pamieci RAM (Out of Memory).")
            break

if __name__ == "__main__":
    if not os.path.exists("data"):
        os.makedirs("data")

    if DRY_RUN:
        run_dry_run()
    else:
        # GLOWNE BADANIA DLA ROZMIAROW USTALONYCH PO DRY-RUNIE
        # np. SIZES = [15, 16, 17, 18, 19, 20, 21]
        SIZES = [10, 11, 12] # UZUPELNIJ po testach
        INSTANCES_PER_SIZE = 20
        ALGORITHMS = ["BB_BFS", "BB_DFS_REC", "BB_LC"]
        UB_METHODS = ["NONE", "RNN"]
        
        with open("results/research_random.csv", "w") as f:
            f.write("Type,Size,InstanceID,Algorithm,UB_Method,BestCost,TimeMs,PeakMemoryKB,Status\n")
            
        print("=== ROZPOCZECIE BADAN GLOWNYCH ===")
        for is_symmetric in [True, False]:
            type_str = "TSP" if is_symmetric else "ATSP"
            
            for size in SIZES:
                for instance_id in range(INSTANCES_PER_SIZE):
                    # 1. Wygeneruj macierz TYLKO RAZ dla danej instancji
                    generate_matrix(size, is_symmetric, "data/python_temp.atsp")
                    
                    # 2. Przebadaj na niej wszystkie warianty algorytmu i UB
                    for algo in ALGORITHMS:
                        for ub in UB_METHODS:
                            print(f"[{type_str} N={size} Inst={instance_id}] Algo={algo} UB={ub} ...", end=" ", flush=True)
                            cost, t, mem, status = run_test_case(algo, ub, is_symmetric, size, instance_id)
                            print(status if status != "OK" else f"{t} ms")
                            
                            with open("results/research_random.csv", "a") as f:
                                f.write(f"{type_str},{size},{instance_id},{algo},{ub},{cost},{t},{mem},{status}\n")
