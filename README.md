# Studentų Rūšiavimo Sistema v3.0

Ši programa leidžia:

- nuskaityti studentų duomenis iš klaviatūros ir iš failų;
- skaičiuoti galutinius balus (pagal **medianą** arba **vidurkį**, pasirenkama strategija);
- rūšiuoti ir skirstyti studentus į *kietiakius* ir *vargšiukus*;
- generuoti atsitiktinius testinius failus;
- atlikti našumo testavimą su dideliais duomenų kiekiais;
- naudoti **paveldėjimą** (`Zmogus` → `Studentas`);
- naudoti **Rule of Three** ir strategijos šabloną galutinio balo skaičiavimui;
- generuoti dokumentaciją su **Doxygen**;
- paleisti vienetų testus su **Catch2** ir CTest;
- **v3.0 nauja:** naudoti atskirą **DLL biblioteką `Skaiciavimai`** galutinio balo skaičiavimui;
- **v3.0 nauja:** sukurti **Windows diegimo programą** (Inno Setup).

---

## Releasų istorija

| Versija | Pagrindiniai pakeitimai | Komentarai apie rezultatus |
|--------|--------------------------|----------------------------|
| v0.1   | Pirmoji pilnai veikianti versija su struktūra ir `std::vector`. | Ši versija suformavo meniu ir bazinę programos logiką. |
| v0.2   | Sugeneruoti dideli testiniai failai (1 000 – 10 000 000 įrašų), įdiegta skirstymo į „vargšiukus“ ir „kietiakius“ logika. | Leido įvertinti, kaip keičiasi trukmė didėjant įrašų skaičiui. |
| v0.3   | Pirmas veikiantis sprendimas su struktūra ir `std::vector`/`std::list`. Skaitymas iš failo, rikiavimas, skirstymas į dvi grupes, bazinis veikimo laiko matavimas. | Parodė, kad sprendimas korektiškai veikia su nedideliais failais, bet didėjant įrašų skaičiui pasimatė našumo problemos. |
| v1.0   | Kodo sutvarkymas, atskirti įvesties/išvesties ir logikos moduliai, aiškesnė projekto struktūra. | Pagerėjo kodo skaitomumas ir lengviau atlikti pakeitimus bei testuoti atskiras dalis. |
| v1.1   | Našumo optimizavimas (rezervuojama atmintis, atsisakyta nereikalingų kopijų, pagerintas skirstymo algoritmas). Atlikti detalūs laiko matavimai skirtingo dydžio failams. | Matavimai parodė, kad po optimizacijų ženkliai sumažėjo rikiavimo ir skirstymo laikas, o skaitymas iš failo išliko dominuojanti dalis. |
| v1.2   | Pereita prie klasės `Studentas`, realizuotas **Rule of Three** (kopijavimo konstruktorius, priskyrimo operatorius, destruktorius). | Patikrinta, kad kopijavimas ir priskyrimas veikia korektiškai, programa stabiliai veikia su didesniais duomenų kiekiais. |
| v1.5   | Įvesta abstrakti bazinė klasė `Zmogus`, iš jos paveldima `Studentas`. Pritaikytas paveldėjimas ir polimorfizmas. | Kodo struktūra tapo lengviau plečiama. Funkcionalumas išliko toks pats, bet OOP požiūriu kodas tapo tvarkingesnis. |
| v2.0   | Pridėta Doxygen dokumentacija (HTML), sukonfigūruotas CMake projektas (biblioteka + vykdomoji programa), įdiegti vienetų testai su Catch2, sutvarkytas README su instrukcijomis ir nuotraukomis. | Vienetų testai rodo, kad pagrindinės funkcijos veikia teisingai. Doxygen tinklalapyje aiškiai matoma klasės struktūra ir funkcijų aprašymai. |
| v3.0   | Pridėta atskira DLL biblioteka `Skaiciavimai` ir Windows diegimo programa (Inno Setup). | Galutinis balas skaičiuojamas per išorinę dinaminę biblioteką, o projektas pateikiamas kaip pilnai įdiegiama programa. |

---

## Naudojamos technologijos

| Funkcija            | Sprendimas                     |
|---------------------|--------------------------------|
| Dokumentacija       | **Doxygen**                    |
| Vienetų testai      | **Catch2 + CTest**             |
| Kodo organizavimas  | **CMake**                      |
| Dinaminė biblioteka | **DLL `Skaiciavimai`**         |
| Diegimo paketas     | **Inno Setup (`setup.iss`)**   |
| OOP principai       | Paveldėjimas, Rule of Three    |
| Strategijos šablonas| Pasirenkamas balo skaičiavimo metodas |

---

## Programos architektūra

### `Zmogus` (abstrakti žmogaus klasė)

- Laukai: `vardas_`, `pavarde_`;
- Abstraktūs metodai: `vardas()`, `pavarde()`, `info()`;
- Bazė visoms „žmogaus“ tipo klasėms (šiuo metu – `Studentas`).

### `Studentas` (paveldi `Zmogus`)

- Laiko:
  - namų darbų pažymių vektorių (`std::vector<double> nd_`);
  - egzamino balą (`double egzaminas_`);
- Implementuoja:
  - **Rule of Three** (kopijavimo konstruktorius, priskyrimo operatorius, destruktorius);
  - strategijos funkciją: `double galBalas(strategy)` (vidurkis / mediana);
  - `readStudent()` – skaito duomenis iš failo arba interaktyviai.

### DLL biblioteka `Skaiciavimai`

- Atskirame projekte realizuota dinaminė biblioteka;
- Eksportuoja funkcijas, kurios:
  - priima pažymių vektorių ir egzamino balą;
  - grąžina galutinį balą;
- Pagrindinė programa vietoje tiesioginio skaičiavimo kreipiasi į `Skaiciavimai.dll`.

### Pagalbinės funkcijos (`Funkcijos.h/.cpp`)

- studentų rūšiavimas ir spausdinimas;
- atsitiktinių studentų failų generavimas;
- nuskaitymas iš failo;
- skirstymas į kietiakius ir vargšiukus;
- našumo testavimas su skirtingo dydžio failais.

---

## Programos paleidimas

### **1. Sukurkite build katalogą**

mkdir build
cd build

### **2. Sugeneruokite projektą su CMake**

cmake -G "MinGW Makefiles" ..

### **3. Sukompiliuokite**

cmake --build .

### **4. Paleiskite programą**

.\studentu_app.exe

---

### **Paleidimas:**

Iš `build/` aplanko:

.\studentu_tests.exe  paleidžia testus

.\studentu_app.exe  paleidžia meniu su galimybėmis

### Kokius rezultatus gauname?
Pagrindinis programos meniu su visomis prieinamomis funkcijomis.
![Meniu langas](images/meniu_app.png)

Paleidus testavimus matome, kad visi parengti vienetų testai įvykdyti sėkmingai
![Testavimų paleidimas](images/testai.png)

“All tests passed (5 assertions in 2 test cases)” rodo, kad abu testai
ir visi 5 patikrinimai davė teisingus rezultatus – pagrindinės funkcijos veikia taip,
kaip tikimasi.

## Diegimo programa (Inno Setup)

Diegimo skriptas aprašytas faile `setup.iss`. Norint sugeneruoti diegimo .exe:

1. Atidarykite `setup.iss` su **Inno Setup** programa.
2. Paspauskite **Build → Compile**.
3. Sugeneruotas diegimo failas (pvz. `StudentuRusiavimasSetup.exe`) bus sukurtas nurodytame kataloge.
4. Vartotojas gali paleisti šį .exe ir įdiegti programą kaip įprastą Windows aplikaciją.

## Doxygen dokumentacija

Sukurti dokumentaciją:

doxygen Doxyfile

Dokumentacija sugeneruojama į katalogą:

docs/html/index.html

Atidarykite naršyklėje:

- `C:/Users/Kompiuteris/Downloads/Naujas_isgit/v_trys_nulis/docs/html/`

### Doxygen generuotos dokumentacijos pavyzdys

Čia galime matyti Doxygen dokumentaciją ir jos pagrindinius puslapius, naudojimo galimybes bei aprašymus. 
Taip atrodo Doxygen pagrindinis langas:
![Doxygen pagrindinis langas](images/doxygen_pagrindinis.png)
Galime matyti visą failų struktūrą šiame darbe
![Visi failai](images/Visi_failai.png)
Čia matome Studento klasę:
![Studento klasės langas](images/Studento_klase.png)
Bei žmogaus klasę:
![Žmogaus klasės langas](images/Zmogaus.png)

Taip pat galime matyti aprašytas funkcijas ir kuriose failuose jos naudojamos
![Funckijos klasėse](images/Funkcijos_klasese.png)

Toliau matome funkcijos `galBalas()` veikimą - parodoma pati funkcija ir aprašomas jos tikslas.
![Funkcijos galBalas dokumentacija](images/galbalas.png)

---

## Pagrindinės funkcijos

### Studentų nuskaitymas iš failo  
Failo formatas:
Vardas Pavarde ND1 ND2 ... Egzaminas

### Galutinio balo skaičiavimas  

galBalas(Studentas::vidurkis)
galBalas(Studentas::mediana)

### Studentų skirstymas į grupes  
- ≥5 — *kietiakiai*
- <5 — *vargšiukai*

### Failų generavimas  

generuotiFaila(nd_count, kiekis)

Sugeneruojami failai:

- studentai_1000.txt
- studentai_10000.txt
- studentai_100000.txt
- studentai_1000000.txt
- studentai_10000000.txt

## Atliktos OOP ir projekto užduoties dalys 

- Paveldėjimas iš abstraktinės bazinės klasės `Zmogus` (polimorfizmas per virtualias funkcijas)  
- **Rule of Three** klasėje `Studentas` (kopijavimo konstruktorius, priskyrimo operatorius, destruktorius)  
- Strategijos šablonas galutinio balo skaičiavimui (`galBalas(Studentas::vidurkis)` / `galBalas(Studentas::mediana)`)  
- Pagrindinė logika išskirta į atskirą dinaminę **DLL biblioteką `Skaiciavimai`** (galutinio balo skaičiavimas per išorinę biblioteką)  
- Vienetų testai su **Catch2** (paleidžiami per CTest), tikrinant pagrindines funkcijas ir klasių elgseną  
- Projektas sukonfigūruotas per **CMake** (atskira biblioteka + vykdomoji programa + testų taikinys)  
- Automatinė dokumentacija su **Doxygen** (HTML tinklalapis su klasių ir funkcijų aprašymais)  
- Studentų rikiavimas, skirstymas į grupes ir veikimo laiko matavimas su skirtingo dydžio failais  
- Parengta **Windows diegimo programa** su Inno Setup (`setup.iss`), leidžianti patogiai įdiegti galutinę v3.0 versiją

## Išvados

Projektas pilnai atitinka užduoties reikalavimus:

- tvarkinga, plečiama architektūra
- aiškiai išskaidytas kodas (klasės, DLL, testai)
- vienetų testai paleidžiami be klaidų
- galima atlikti našumo analizę su dideliais duomenų kiekiais
- Doxygen dokumentacija pasiekiama kaip HTML tinklalapis
- paruoštas diegimo paketas galutiniam vartotojui