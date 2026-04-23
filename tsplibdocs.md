### TSPLIB 95

```
GerhardReinelt
UniversitatHeidelberg
InstitutfurAngewandteMathematik
ImNeuenheimerFeld 294
D-69120Heidelberg
Gerhard.Reinelt@IWR.Uni-Heidelberg.DE
```
TSPLIBisalibraryofsampleinstancesfortheTSP(andrelatedproblems)fromvarious

sourcesandofvarioustypes. Instancesofthefollowingproblemclassesareavailable.

Symmetrictravelingsalesmanproblem(TSP)

Givenasetofnnodesanddistancesforeachpairofnodes,ndaroundtripofminimal

totallengthvisitingeachnodeexactlyonce. Thedistancefromnodeitonodej isthe

sameasfromnodejtonodei.

Hamiltoniancycleproblem(HCP)

Givenagraph,testifthegraphcontainsaHamiltoniancycleornot.

Asymmetrictravelingsalesmanproblem(ATSP)

Givenasetofnnodesanddistancesforeachpairofnodes,ndaroundtripofminimal

totallengthvisitingeachnodeexactlyonce.Inthiscase,thedistancefromnodeitonode

jandthedistancefromnodejtonodeimaybedierent.

Sequential orderingproblem(SOP)

Thisproblemisanasymmetrictravelingsalesmanproblemwithadditionalconstraints.

Givenasetofnnodesanddistancesforeachpairofnodes,ndaHamiltonianpathfrom

node 1 tonodenofminimallengthwhichtakesgivenprecedenceconstraintsintoaccount.

Eachprecedenceconstraintrequiresthatsomenodeihastobevisitedbeforesomeother

nodej.

Capacitatedvehicleroutingproblem(CVRP)

Wearegivenn 1 nodes,onedepotanddistancesfromthenodestothedepot,aswellas

betweennodes.Allnodeshavedemandswhichcanbesatisedbythedepot.Fordelivery

tothenodes,truckswithidenticalcapacitiesareavailable.Theproblemistondtoursfor

thetrucksofminimaltotallengththatsatisfythenodedemandswithoutviolatingtruck

capacityconstraint.Thenumberoftrucksisnotspecied.Eachtourvisitsasubsetofthe

nodesandstartsandterminatesatthedepot. (Remark:Insomedatalesacollectionof

alternatedepotsisgiven.ACVRPisthengivenbyselectingoneofthesedepots.)

Except,fortheHamiltoniancycleproblems,allproblemsaredenedonacompletegraph

and,atpresent,alldistancesareintegernumbers. Thereisapossibilitytorequirethat

certainedgesappearinthesolutionofaproblem.


1. The le format

Eachleconsistsofaspecication partandofadata part. Thespecicationpart

containsinformationontheleformatandonitscontents.Thedatapartcontainsexplicit

data.

1.1 Thespecicationpart

Allentriesinthissectionareoftheform<keyword> : <value>,where<keyword>de-

notesanalphanumericalkeywordand<value>denotesalphanumericalornumericaldata.

Theterms<string>,<integer>and<real>denotecharacterstring,integerorrealdata,

respectively. Theorderofspecicationofthekeywordsinthedataleis arbitrary(in

principle),butmustbeconsistent,i.e.,wheneverakeywordisspecied,allnecessaryin-

formationforthecorrectinterpretationofthekeywordhastobeknown. Belowwegivea

listofallavailablekeywords.

1.1.1 NAME:<string>

Identiesthedatale.

1.1.2 TYPE:<string>

Speciesthetypeofthedata.Possibletypesare

```
TSP Dataforasymmetrictravelingsalesmanproblem
ATSP Dataforanasymmetrictravelingsalesmanproblem
SOP Dataforasequentialorderingproblem
HCP Hamiltoniancycleproblemdata
CVRP Capacitatedvehicleroutingproblemdata
TOUR Acollectionoftours
```
1.1.3 COMMENT:<string>

Additionalcomments(usuallythenameofthecontributororcreatoroftheproblemin-

stanceisgivenhere).

1.1.4 DIMENSION:<integer>

ForaTSPorATSP,thedimensionisthenumberofitsnodes.ForaCVRP,itisthetotal

numberofnodesanddepots. ForaTOURleitisthedimensionofthecorresponding

problem.

1.1.5 CAPACITY:<integer>

SpeciesthetruckcapacityinaCVRP.

1.1.6 EDGEWEIGHTTYPE:<string>

Specieshowtheedgeweights(ordistances)aregiven.Thevaluesare

```
EXPLICIT Weightsarelistedexplicitlyinthecorrespondingsection
EUC2D WeightsareEuclideandistancesin2-D
EUC3D WeightsareEuclideandistancesin3-D
```

```
MAX2D Weightsaremaximumdistancesin2-D
MAX3D Weightsaremaximumdistancesin3-D
MAN2D WeightsareManhattandistancesin2-D
MAN3D WeightsareManhattandistancesin3-D
CEIL2D WeightsareEuclideandistancesin2-Droundedup
GEO Weightsaregeographicaldistances
ATT Specialdistancefunctionforproblemsatt48andatt
XRAY1 Specialdistancefunctionforcrystallographyproblems(Version1)
XRAY2 Specialdistancefunctionforcrystallographyproblems(Version2)
SPECIAL Thereisaspecialdistancefunctiondocumentedelsewhere
```
1.1.7 EDGEWEIGHTFORMAT:<string>

Describestheformatoftheedgeweightsiftheyaregivenexplicitly.Thevaluesare

```
FUNCTION Weightsaregivenbyafunction(seeabove)
FULLMATRIX Weightsaregivenbyafullmatrix
UPPERROW Uppertriangularmatrix(row-wisewithoutdiagonalentries)
LOWERROW Lowertriangularmatrix(row-wisewithoutdiagonalentries)
UPPERDIAGROW Uppertriangularmatrix(row-wiseincludingdiagonalentries)
LOWERDIAGROW Lowertriangularmatrix(row-wiseincludingdiagonalentries)
UPPERCOL Uppertriangularmatrix(column-wisewithoutdiagonalentries)
LOWERCOL Lowertriangularmatrix(column-wisewithoutdiagonalentries)
UPPERDIAGCOL Uppertriangularmatrix(column-wiseincludingdiagonalentries)
LOWERDIAGCOL Lowertriangularmatrix(column-wiseincludingdiagonalentries)
```
1.1.7 EDGEDATAFORMAT:<string>

Describestheformatinwhichtheedgesofagrapharegiven,ifthegraphisnotcomplete.

Thevaluesare

```
EDGELIST Thegraphisgivenbyanedgelist
ADJLIST Thegraphisgivenasanadjacencylist
```
1.1.9 NODECOORDTYPE:<string>

Specieswhethercoordinatesareassociatedwitheachnode(which,forexamplemaybe

usedforeithergraphicaldisplayordistancecomputations).Thevaluesare

```
TWODCOORDS Nodesarespeciedbycoordinatesin2-D
THREEDCOORDS Nodesarespeciedbycoordinatesin3-D
NOCOORDS Thenodesdonothaveassociatedcoordinates
```
ThedefaultvalueisNOCOORDS.

1.1.10 DISPLAYDATATYPE:<string>

Specieshowagraphicaldisplayofthenodescanbeobtained.Thevaluesare

```
COORDDISPLAY Displayisgeneratedfromthenodecoordinates
TWODDISPLAY Explicitcoordinatesin2-Daregiven
NODISPLAY Nographicaldisplayispossible
```
Thedefault valueis COORDDISPLAY if node coordinates are specied and NODISPLAY

otherwise.


### 1.1.11 EOF:

Terminatestheinputdata.Thisentryisoptional.

1.2 Thedata part

Dependingonthechoiceofspecicationssomeadditionaldatamaybe required. These

dataaregivenincorrespondingdatasectionsfollowingthespecicationpart. Eachdata

sectionbeginswiththecorrespondingkeyword.Thelengthofthesectioniseitherimplicitly

knownfromtheformatspecication,orthesectionisterminatedbyanappropriateend-

of-sectionidentier.

1.2.1 NODECOORDSECTION:

Nodecoordinatesaregiveninthissection. Eachlineisoftheform

```
<integer><real><real>
```
ifNODECOORDTYPEisTWODCOORDS,or

```
<integer><real><real><real>
```
if NODECOORDTYPE is THREEDCOORDS. Theintegersgive thenumberof therespective

nodes.Therealnumbersgivetheassociatedcoordinates.

1.2.2 DEPOTSECTION:

Containsalistofpossiblealternatedepotnodes.Thislististerminatedbya1.

1.2.3 DEMANDSECTION:

ThedemandsofallnodesofaCVRParegivenintheform(perline)

```
<integer><integer>
```
Therstintegerspeciesanodenumber,theseconditsdemand. Thedepotnodesmust

alsooccurinthissection.Theirdemandsare0.

1.2.4 EDGEDATASECTION:

EdgesofagrapharespeciedineitherofthetwoformatsallowedintheEDGEDATAFORMAT

entry.IfthetypeisEDGELIST,thentheedgesaregivenasasequenceoflinesoftheform

```
<integer><integer>
```
eachentrygivingtheterminalnodesofsomeedge.Thelististerminatedbya1.

IfthetypeisADJLIST,thesectionconsists ofa listofadjacencylistsfornodes. The

adjacencylistofanodexisspeciedas

```
<integer><integer>:::<integer> 1
```
wheretherstintegergivesthenumberofnodexandthefollowingintegers(terminated

by 1 )thenumbersofnodesadjacenttox. Thelistofadjacencylistsisterminatedby

anadditional1.


### 1.2.5 FIXEDEDGESSECTION:

Inthissection,edgesarelistedthatarerequiredtoappearineachsolutiontotheproblem.

Theedgestobexedaregivenintheform(perline)

```
<integer><integer>
```
meaningthattheedge(arc)fromtherstnodetothesecondnodehastobecontainedin

asolution.Thissectionisterminatedbya1.

1.2.6 DISPLAYDATASECTION:

IfDISPLAYDATATYPEisTWODDISPLAY,the2-dimensionalcoordinatesfromwhichadisplay

canbegeneratedaregivenintheform(perline)

```
<integer><real><real>
```
Theintegersspecifytherespectivenodesandtherealnumbersgivetheassociatedcoordi-

nates.

1.2.7 TOURSECTION:

Acollectionoftoursisspeciedinthissection.Eachtourisgivenbyalistofintegersgiving

thesequenceinwhichthenodesarevisitedinthistour.Everysuchtouristerminatedby

a1. Anadditional 1 terminatesthissection.

1.2.8 EDGEWEIGHTSECTION:

TheedgeweightsaregivenintheformatspeciedbytheEDGEWEIGHTFORMATentry.At

present,allexplicitdataisintegralandisgiveninoneofthe(self-explanatory)matrix

formats.withimplicitlyknownlengths.


2. The distance functions

ForthevariouschoicesofEGDEWEIGHTTYPE,wenowdescribe thecomputationsofthe

repsectivedistances. Ineachcasewegivea(simplied)C-implementationfor comput-

ingthedistancesfromtheinputcoordinates. Allcomputationsinvolving
oating-point

numbersarecarriedoutindoubleprecisionarithmetic. Theintegersareassumedtobe

representedin32-bitwords. Sincedistancesarerequiredtobeintegral,weroundtothe

nearestinteger(inmostcases).BelowwehaveusedtheCroundingfunction\nint".

2.1 Euclideandistance (L 2 -metric)

ForedgeweighttypeEUC2DandEUC3D,
oatingpointcoordinatesmustbespeciedfor

eachnode.Letx[i],y[i],andz[i]bethecoordinatesofnodei.

Inthe2-dimensionalcasethedistancebetweentwopointsiandjiscomputedasfollows:

```
xd = x[i] - x[j];
yd = y[i] - y[j];
dij = nint( sqrt( xd*xd + yd*yd) );
```
Inthe3-dimensionalcasewehave:

```
xd = x[i] - x[j];
yd = y[i] - y[j];
zd = z[i] - z[j];
dij = nint( sqrt( xd*xd + yd*yd + zd*zd) );
```
wheresqrtistheCsquarerootfunction.

2.2 Manhattandistance(L 1 -metric)

DistancesaregivenasManhattandistancesiftheedgeweighttypeisMAN2DorMAN3D.

Theyarecomputedasfollows.

2-dimensionalcase:

```
xd = abs( x[i] - x[j] );
yd = abs( y[i] - y[j] );
dij = nint( xd + yd );
```
3-dimensionalcase:

```
xd = abs( x[i] - x[j] );
yd = abs( y[i] - y[j] );
zd = abs( z[i] - z[j] );
dij = nint( xd + yd + zd );
```
2.3 Maximumdistance(L 1 -metric)

MaximumdistancesarecomputediftheedgeweighttypeisMAX2DorMAX3D.

2-dimensionalcase:

```
xd = abs( x[i] - x[j] );
yd = abs( y[i] - y[j] );
dij = max( nint( xd ), nint( yd ) ) );
```

3-dimensionalcase:

```
xd = abs( x[i] - x[j] );
yd = abs( y[i] - y[j] );
zd = abs( z[i] - z[j] );
dij = max( nint( xd ), nint( yd ), nint( zd ) );
```
2.4 Geographicaldistance

Ifthetravelingsalesmanproblemisageographicalproblem,thenthenodescorrespondto

pointsontheearthandthedistancebetweentwopointsistheirdistanceontheidealized

spherewithradius6378.388kilometers. Thenodecoordinatesgivethegeographicallat-

itudeandlongitudeofthecorrespondingpointontheearth. Latitudeandlongitudeare

givenintheformDDD.MMwhereDDDarethedegreesandMMtheminutes.Apositivelati-

tudeisassumedtobe\North",negativelatitudemeans\South".Positivelongitudemeans

\East",negativelatitudeisassumedtobe\West".Forexample,theinputcoordinatesfor

Augsburgare48.23and10.53,meaning 48 o23Northand 10 o53East.

Letx[i]andy[i]becoordinatesforcityiintheaboveformat.Firsttheinputisconverted

togeographicallatitudeandlongitudegiveninradians.

```
PI = 3.141592;
deg = nint( x[i] );
min = x[i] - deg;
latitude[i] = PI * (deg + 5.0 * min / 3.0 ) / 180.0;
deg = nint( y[i] );
min = y[i] - deg;
longitude[i] = PI * (deg + 5.0 * min / 3.0 ) / 180.0;
```
Thedistancebetweentwodierentnodesiandjinkilometersisthencomputedasfollows:

```
RRR = 6378.388;
q1 = cos( longitude[i] - longitude[j] );
q2 = cos( latitude[i] - latitude[j] );
q3 = cos( latitude[i] + latitude[j] );
dij = nint( (RRR * acos( 0.5*((1.0+q1)*q2 - (1.0-q1)*q3) ) + 1.0);
```
Thefunction\acos"istheinverseofthecosinefunction.

2.5 Pseudo-Euclideandistance

TheedgeweighttypeATTcorrespondstoaspecial\pseudo-Euclidean"distancefunction.

Letx[i]andy[i]bethecoordinatesofnodei. Thedistancebetweentwopointsiandj

iscomputedasfollows:

```
xd = x[i] - x[j];
yd = y[i] - y[j];
rij = sqrt( (xd*xd + yd*yd) / 10.0 );
tij = nint( rij );
if (tij<rij) dij = tij + 1;
else dij = tij;
```

2.6 Ceilingof theEuclideandistance

The edge weight type CEIL2D requires thatthe 2-dimensional Euclidean distancesis

roundeduptothenextinteger.

2.7 Distancefor crystallographyproblems

WehaveincludedintoTSPLIBthecrystallographyproblemsasdescribedin[1]. These

problemsarenotexplicitlygivenbutsubroutinesareprovidedtogeneratethe 12 problems

mentionedinthisreferenceandsubproblemsthereof(seesection3.2).

Tocomputedistancesfortheseproblemsthemovementofthreemotorshastobetakeninto

consideration. Therearetwotypesofdistancefunctions: onethatassumesequalspeed

ofthemotors (XRAY1) and onethatusesdierent speeds(XRAY2). Thecorresponding

distancefunctionsaregivenasFORTRANimplementations(lesdeq.f,resp.duneq.f)in

thedistributionle.

Forobtainingintegerdistances,weproposetomultiplythedistancescomputed bythe

originalsubroutinesby100.0androundtothenearestinteger.

WelistourmodieddistancefunctionforthecaseofequalmotorspeedsintheFORTRAN

versionbelow.

INTEGER FUNCTION ICOST(V,W)
INTEGER V,W
DOUBLE PRECISION DMIN1,DMAX1,DABS
DOUBLE PRECISION DISTP,DISTC,DISTT,COST
DISTP=DMIN1(DABS(PHI(V )-PHI( W)),DAB S(DABS (PHI(V) -PHI(W) )-360. 0E+0))
DISTC=DABS(CHI(V)-CHI( W))
DISTT=DABS(TWOTH(V)-TW OTH(W) )
COST=DMAX1(DISTP/1.00E +0,DIS TC/1.0E +0,DIS TT/1.00 E+0)
C *** Make integral distances ***
ICOST=AINT(100.0E+0*CO ST+0.5 E+0)
RETURN
END

ThenumbersPHI(), CHI(),andTWOTH()aretherespectivex-,y-,andz-coordinatesof

thepointsinthegeneratedtravelingsalesmanproblems. Note,thatTSPLIB95contains

onlytheoriginaldistancecomputationwithouttheabovemodication.

2.7 Verication

Toverifycorrectnessofthedistancefunctionimplementationswegivethelengthofsome

\canonical"tours 1 ; 2 ; 3 ;:::;n.

Thecanonicaltoursfor pcb442, gr666, and att532havelengths 221 440, 423 710, and

309 636,respectively.

Thecanonicaltourfortheproblemxray14012(the8thproblemconsideredin[21])with

distanceXRAY1haslength 15429 219.WithdistanceXRAY2ithasthelength 12943 294.


3. Description of the library les

Inthissectionwegivealistofallprobleminstancesthatarecurrentlyavailabletogether

withinformationonthelengthofoptimaltoursorlowerandupperboundsforthislength

(ifavailable).

3.1 Symmetrictraveling salesmanproblems

TheTSPinstancesarecontainedindirectorytsp. Table 1 givestheproblemnamesalong

withnumberofcities,problemtype,andknownlowerandupperboundsfortheoptimal

tourlength(asinglenumberindicatingthattheoptimallengthis known). Theentry

MATRIXindicatesthatthedataisgiveninoneofthematrixformatsof1.1.7. Thenames

ofthecorrespondingdatalesareobtainedbyappendingthesux\.tsp"totheproblem

name. Someoptimaltoursarealsoprovided. Thecorrespondingleshavenameswith

sux\.opt.tour".

```
Name #cities Type Bounds
a280 280 EUC2D 2579
ali535 535 GEO 202310
att48 48 ATT 10628
att532 532 ATT 27686
bayg29 29 GEO 1610
bays29 29 GEO 2020
berlin52 52 EUC2D 7542
bier127 127 EUC2D 118282
brazil58 58 MATRIX 25395
brd14051 14051 EUC2D [468942,469935]
brg180 180 MATRIX 1950
burma14 14 GEO 3323
ch130 130 EUC2D 6110
ch150 150 EUC2D 6528
d198 198 EUC2D 15780
d493 493 EUC2D 35002
d657 657 EUC2D 48912
d1291 1291 EUC2D 50801
d1655 1655 EUC2D 62128
d2103 2103 EUC2D [79952,80529]
d15112 15112 EUC2D [1564590,1574558]
d18512 18512 EUC2D [644650,645923]
dantzig42 42 MATRIX 699
dsj1000 1000 CEIL2D 18659688
eil51 51 EUC2D 426
eil76 76 EUC2D 538
eil101 101 EUC2D 629
```
```
Table 1 Symmetrictravelingsalesmanproblems(PartI)
```

## Name #cities Type Bounds

```
fl1577 1577 EUC2D [22204,22249]
```
pla33810 33810 CEIL2D [65913275,66138592]
pla85900 85900 CEIL2D [141904862,142514146]


```
rl5915 5915 EUC2D [565040,565544]
rl5934 5934 EUC2D [554070,556050]
```
         - fl417 417 EUC2D
      - fl1400 1400 EUC2D
   - fnl4461 4461 EUC2D fl3795 3795 EUC2D [28723,28772]
         - fri26 26 MATRIX
      - gil262 262 EUC2D
            - gr17 17 MATRIX
            - gr21 21 MATRIX
            - gr24 24 MATRIX
            - gr48 48 MATRIX
            - gr96 96 GEO
         - gr120 120 MATRIX
         - gr137 137 GEO
         - gr202 202 GEO
         - gr229 229 GEO
         - gr431 431 GEO
         - gr666 666 GEO
            - hk48 48 MATRIX
   - kroA100 100 EUC2D
   - kroB100 100 EUC2D
   - kroC100 100 EUC2D
   - kroD100 100 EUC2D
   - kroE100 100 EUC2D
   - kroA150 150 EUC2D
   - kroB150 150 EUC2D
   - kroA200 200 EUC2D
   - kroB200 200 EUC2D
      - lin105 105 EUC2D
      - lin318 318 EUC2D
- linhp318 318 EUC2D
   - nrw1379 1379 EUC2D
            - p654 654 EUC2D
         - pa561 561 MATRIX
      - pcb442 442 EUC2D
   - pcb1173 1173 EUC2D
   - pcb3038 3038 EUC2D
   - pla7397 7397 CEIL2D
            - pr76 76 EUC2D Name #cities Type Bounds
         - pr107 107 EUC2D
         - pr124 124 EUC2D
         - pr136 136 EUC2D
         - pr144 144 EUC2D
         - pr152 152 EUC2D
         - pr226 226 EUC2D
         - pr264 264 EUC2D
         - pr299 299 EUC2D
         - pr439 439 EUC2D
      - pr1002 1002 EUC2D
      - pr2392 2392 EUC2D
         - rat99 99 EUC2D
      - rat195 195 EUC2D
      - rat575 575 EUC2D
      - rat783 783 EUC2D
         - rd100 100 EUC2D
         - rd400 400 EUC2D
      - rl1304 1304 EUC2D
      - rl1323 1323 EUC2D
      - rl1889 1889 EUC2D
         - si175 175 MATRIX rl11849 11849 EUC2D [920847,923473]
         - si535 535 MATRIX
      - si1032 1032 MATRIX
            - st70 70 EUC2D
   - swiss42 42 MATRIX
         - ts225 225 EUC2D
      - tsp225 225 EUC2D
            - u159 159 EUC2D
            - u574 574 EUC2D
            - u724 724 EUC2D
         - u1060 1060 EUC2D
         - u1432 1432 EUC2D
         - u1817 1817 EUC2D
         - u2152 2152 EUC2D
         - u2319 2319 EUC2D
- ulysses16 16 GEO
- ulysses22 22 GEO
      - vm1084 1084 EUC2D usa13509 13509 EUC2D [19947008,20167722]
      - vm1748 1748 EUC2D


Crystallographyproblems

Inthele xray.problemsindirectorytspwedistributetheroutineswrittenbyBland

andShallcrossandthenecessarydatatogeneratethecrystallographyproblemsdiscussed

in[1].Thelexray.problemsisoneleintowhichthesinglelesmentionedinthesequel

havebeenmerged. Thesesingleleshavetobeextractedfromxray.problemsusingan

editor.Thefollowingoriginallesareprovided

```
read.me deq.f duneq.f daux.f gentsp.f
a.data b.data d.data e.data f.data
```
Inaddition wehaveincludedspeciallyprepared datales togenerate the 12 problems

mentionedin[1].Theleshavethenamesxray1.datathroughxray12.data.

Usingthesedatales 12 symmetricTSPscanbegeneratedusingtheprogramgentsp.f.

Weproposeto nametherespectiveprobleminstancesxray4472, xray2950, xray7008,

xray2762,xray6922,xray9070,xray5888,xray14012,xray5520,xray13804,xray14464,

andxray13590.

Toverifythecorrectuseofthegeneratingroutineswelistpartofthelexray14012.tsp.

NAME : xray
COMMENT : Crystallography problem 8 (Bland/Shallcross)
TYPE : TSP
DIMENSION : 14012
EDGEWEIGHTTYPE : XRAY
NODECOORDSECTION

```
1 -91.802854544029 -6.4097888697337 176.
2 -87.715643397938 -6.4659384343446 165.
3 -83.587211962870 -6.4895404648110 163.
4 -79.460007412434 -6.4797580053949 165.
:
:
14009 100.539992581837 6.4797580053949 165.
14010 96.412788031401 6.4895404648110 163.
14011 92.284356596333 6.4659384343446 165.
14012 88.197145450242 6.4097888697337 176.
```
3.2 Hamiltoniancycleproblems

InstancesoftheHamiltoniancycleproblemarecontainedinthedirectoryhcp.Atpresent,

wehavethedatales

```
alb1000.hcp alb3000b.hcp alb3000e.hcp alb2000.hcp alb3000c.hcp
alb4000.hcp alb3000a.hcp alb3000d.hcp alb5000.hcp
```
EveryinstancecontainsaHamiltoniancyclewhichisgiveninthecorresponding.opt.tour

le.Inprobleminstancealb4000twoedgesarexed.

Inadditiontotheseles,thedirectorycontainstheC-programtspleap.cbyM.Junger

andG.Rinaldi.ThisprogramcanbeusedtogenerateTSPinstances(inTSPLIBformat)


originatingfromtheproblemofdecidingwhetheran(r,s)-leaperonamxnchessboardcan

startatsomesquareoftheboard,visiteachsquareexactlyonce,andreturntoitsstarting

square.Adetaileddocumentationisgivenintheletspleap.c.

3.3 Asymmetrictraveling salesmanproblems

Table 2 liststheATSPinstances(indirectoryatsp)togetherwiththeiroptimalsolution

values. Thenamesofthecorrespondingdatalesareobtainedbyappendingthesux

\.atsp"totheproblemname.Thedatalesforproblemsftv90,ftv100,ftv110,ftv120,

ftv130,ftv140,ftv150,andftv160arenotpresent.Theseinstancesareobtainedfrom

ftv170. E.g.,ftv120isthesubproblemofftv170denedbytherst 121 nodes,ftv

isdenedbytherst 131 nodes,etc.

```
Name #cities Type Optimum
br17 17 MATRIX 39
ft53 53 MATRIX 6905
ft70 70 MATRIX 38673
ftv33 34 MATRIX 1286
ftv35 36 MATRIX 1473
ftv38 39 MATRIX 1530
ftv44 45 MATRIX 1613
ftv47 48 MATRIX 1776
ftv55 56 MATRIX 1608
ftv64 65 MATRIX 1839
ftv70 71 MATRIX 1950
ftv90 91 MATRIX 1579
ftv100 101 MATRIX 1788
ftv110 111 MATRIX 1958
ftv120 121 MATRIX 2166
ftv130 131 MATRIX 2307
ftv140 141 MATRIX 2420
ftv150 151 MATRIX 2611
ftv160 161 MATRIX 2683
ftv170 171 MATRIX 2755
kro124 124 MATRIX 36230
p43 43 MATRIX 5620
rbg323 323 MATRIX 1326
rbg358 358 MATRIX 1163
rbg403 403 MATRIX 2465
rbg443 443 MATRIX 2720
ry48p 48 MATRIX 14422
```
```
Table 2 Asymmetrictravelingsalesmanproblems
```
3.4 Sequentialordering problems

EveryinstanceofasequentialorderingproblemisgivenbyafullmatrixCofthefollowing

kind.Ifnodeihastoprecedenodej,thenCjiissetto1. Cisassumedtobetransitively

closedwithrespecttoprecedences,i.e.,ifihastoprecedejandjhastoprecedek,then


itisimpliedthatihastoprecedekand,therefore,alsoCkihastobesetto1.Because

werequire,thatnode 1 istherstnodeandnodenisthelastnodeineachfeasiblepath,

aSOPprobleminstancealwayshasCi 1 =1,foralli= 2 ;:::;n,andCnj=1,forall

j= 1 ;:::;n1. TheentryC 1 nissettoinnity. AllotherentriesofCarenonnegative

integervalues.

```
Name #nodes #prec. Type Bounds
ESC07 9 6 MATRIX 2125
ESC11 13 3 MATRIX 2075
ESC12 14 7 MATRIX 1675
ESC25 27 9 MATRIX 1681
ESC47 49 10 MATRIX 1288
ESC63 65 95 MATRIX 62
ESC78 80 77 MATRIX 18230
br17.10 17 10 MATRIX 55
br17.12 17 12 MATRIX 55
ft53.1 54 12 MATRIX [7438,7570]
ft53.2 54 25 MATRIX [7630,8335]
ft53.3 54 48 MATRIX [9473,10935]
ft53.4 54 63 MATRIX 14425
ft70.1 71 17 MATRIX 39313
ft70.2 71 35 MATRIX [39739,41778]
ft70.3 71 68 MATRIX [41305,44732]
ft70.4 71 86 MATRIX [52269,53882]
kro124p.1 101 25 MATRIX [37722,42845]
kro124p.2 101 49 MATRIX [38534,45848]
kro124p.3 101 97 MATRIX [40967,55649]
kro124p.4 101 131 MATRIX [64858,80753]
p43.1 44 9 MATRIX 27990
p43.2 44 20 MATRIX [28175,28330]
p43.3 44 37 MATRIX [28366,28680]
p43.4 44 50 MATRIX [69569,82960]
prob42 42 10 MATRIX 243
prob100 100 41 MATRIX [1024,1385]
rbg048a 50 192 MATRIX 351
rbg050c 52 256 MATRIX 467
rbg109a 111 622 MATRIX 1038
rbg150a 152 952 MATRIX [1748,1750]
rbg174a 176 1113 MATRIX 2053
rbg253a 255 1721 MATRIX [2928,2987]
rbg323a 325 2412 MATRIX [3136,3221]
rbg341a 343 2542 MATRIX [2543,2854]
rbg358a 360 3239 MATRIX [2518,2758]
rbg378a 380 3069 MATRIX [2761,3142]
ry48p.1 49 11 MATRIX [15220,15935]
ry48p.2 49 23 MATRIX [15524,17071]
ry48p.3 49 42 MATRIX [18156,20051]
ry48p.4 49 58 MATRIX [29967,31446]
```
```
Table 3 Sequentialorderingproblems
```

Table 3 liststheSOPinstances(indirectorysop)togetherwiththeirknownlowerand

upperboundsfortheoptimalpathlength.Thenamesofthecorrespondingdatalesare

obtainedbyappendingthesux\.sop"totheproblemname.

3.5 Capacitatedvehicleroutingproblems

Dataforcapacitatedvehicleroutingproblemsiscontainedinthedirectoryvrp. Datales

havesux\.vrp". Atpresent,wehavethedatales

```
att48.vrp eil30.vrp eil7.vrp eilB76.vrp eil13.vrp
eil31.vrp eilA101.vrp eilC76.vrp eil22.vrp eil33.vrp
eilA76.vrp eilD76.vrp eil23.vrp eil51.vrp eilB101.vrp
gil262.vrp
```
Variousproblemscanbedenedonthesedatasets,e.g.,dependingonwhetherthenumber

ofvehiclesisxed,sowedonotlistoptimalsolutionshere. Somevaluesaregiveninthe

datalesthemselves.

3.6 Furtherspecialles

Inadditiontothedataandsolutionles,thefollowingspeciallesarecontainedinthe

library.

```
TSPLIBVERSION: Givesthecurrentversionofthelibrary
README: AshortinformationonTSPLIB
DOC.PS: DescriptionofTSPLIB(PostScript)
```
4. Remarks

```
1.Theproblemlin318isoriginallyaHamiltonianpathproblem.Oneobtainsthisprob-
lembyaddingtheadditionalrequirementthattheedgefrom 1 to 214 iscontainedin
thetour.Thedataisgiveninlinhp318.tsp.
```
```
2.Somedatasetsarereferredtobydierentnamesintheliterature.Belowwegivethe
correspondingnamesusedin[3]and[2].
```
```
TSPLIB [3] [2] TSPLIB [3] [2]
att48 ATT048 - att532 ATT532 -
dantzig42 - 42 eil101 EIL10 -
eil51 EIL08 - eil76 EIL09 -
gil262 GIL249 - gr120 - 120
gr137 GH137 137 gr202 GH202 202
gr229 GH229 229 gr431 GH431 431
gr666 GH666 666 gr96 GH096 96
hk48 - 48H kroA100 KRO124 100A
kroB100 KRO125 100B kroC100 KRO126 100C
kroD100 KRO127 100D kroE100 KRO128 100E
```

```
kroA150 KRO30 - kroB150 KRO31 -
kroA200 KRO32 - kroB200 KRO33 -
lin105 LK105 - lin318 LK318 -
linhp318 LK318P - pr1002 TK1002 -
pr107 TK107 - pr124 TK124 -
pr136 TK136 - pr144 TK144 -
pr152 TK152 - pr226 TK226 -
pr2392 TK2392 - pr264 TK264 -
pr299 TK299 - pr439 TK439 -
pr76 TK076 - st70 KRO070 70
```
```
3.SomevehicleroutingproblemsarealsoavailableinaTSPversion.Herethedepotsare
justtreatedasnormalnodes. Theproblemgil262originallycontainedtwoidentical
nodes,ofwhichonewaseliminated.
```
```
4.Potentialcontributorsto this libraryshould providetheir data les in appropriate
formatandcontact
GerhardReinelt
InstitutfurAngewandteMathematik,UniversitatHeidelberg
ImNeuenheimerFeld294,D-69120Heidelberg
Germany
Tel (6221) 563171
Fax (6221) 565634
E-Mail Gerhard.Reinelt@IWR.Uni-H eidelbe rg.DE
5.Informationsonnewboundsoroptimalsolutionsforlibraryproblemsaswellasref-
erences to computationalstudies (to be includedin thelist of references)are also
appreciated.
```
5. Access

TSPLIBisavailableatvariouslocations.

InterdisziplinaresZentrumfurWissenschaftlichesRechnen(IWR),Heidelberg

WorldWideWeb:

```
http://www.iwr.uni-heidel berg.de /iwr/co mopt/s oft/TSP LIB95/ TSPLIB. html
```
Konrad-Zuse-ZentrumfurInformationstechnik(ZIB),Berlin

WorldWideWeb:

```
ftp://elib.zib-berlin.de/ pub/mp- testdat a/tsp/ index.h tml
```
ForfurtherinformationonhowtousetheelectroniclibraryfacilitiesatZIBsendamail

justcontaining\help"toelib@ZIB-Berlin.de.

CenterforResearchonParallel Computation(CRPC),Houston

Gopher:

```
gopher://softlib.rice.edu /11/sof tlib/ts plib
```
Anonymousftp:

```
ftp://softlib.rice.edu/pu b/tspli b
```

References

```
1.R.E.Bland&D.F.Shallcross(1989). LargeTraveling SalesmanProblemsArising
fromExperimentsinX-rayCrystallography: APreliminaryReportonComputation,
OperationsResearchLetters 8 ,125{128.
2.M.Grotschel& O.Holland(1991). SolutionofLarge-ScaleSymmetricTravelling
SalesmanProblems, MathematicalProgramming 51 ,141{202.
3.M.W.Padberg&G.Rinaldi(1991). ABranch&CutAlgorithmfortheResolution
ofLarge-scaleSymmetricTravelingSalesmanProblems, SIAMReview 33 ,60{100.
```

