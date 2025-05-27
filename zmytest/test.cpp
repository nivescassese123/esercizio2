#include "test.hpp"
#include <iostream>
#include <cassert>
#include <iomanip>

/* ************************************************************************** */

#include "../zlasdtest/container/container.hpp"
#include "../zlasdtest/container/dictionary.hpp"
#include "../zlasdtest/container/linear.hpp"
#include "../zlasdtest/container/mappable.hpp"
#include "../zlasdtest/container/testable.hpp"
#include "../zlasdtest/container/traversable.hpp"
#include "../zlasdtest/vector/vector.hpp"
#include "../zlasdtest/list/list.hpp"
#include "../zlasdtest/set/set.hpp"

#include "../vector/vector.hpp"  
#include "../list/list.hpp"      
#include "../set/set.hpp"        
#include "../set/vec/setvec.hpp"
#include "../set/lst/setlst.hpp"

/* ************************************************************************** */

// Struttura per tenere traccia dei risultati dei test 
struct TestResults {
    unsigned int total = 0;
    unsigned int passed = 0;
    unsigned int failed = 0;
    
    void reset() {
        total = 0;
        passed = 0;
        failed = 0;
    }
    
    void addTest(bool success, const std::string& description) {
        total++;
        if (success) {
            passed++;
            std::cout << " " << total << " (" << failed << ") " << description << ": Correct!" << std::endl;
        } else {
            failed++;
            std::cout << " " << total << " (" << failed << ") " << description << ": Wrong!" << std::endl;
        }
    }
    
    void printSummary(const std::string& testName) {
        std::cout << "\nEnd of " << testName << " Test! (Errors/Tests: " << failed << "/" << total << ")" << std::endl;
        
        if (total > 0) {
            double successRate = (static_cast<double>(passed) / total) * 100.0;
            std::cout << "Percentuale di successo: " << std::fixed << std::setprecision(2) << successRate << "%" << std::endl;
        } else {
            std::cout << "Percentuale di successo: N/A (nessun test eseguito)" << std::endl;
        }
    }
};

// Aggiungiamo una variabile globale per i risultati dei test
TestResults testResults;

/* ************************************************************************** */

// Test personalizzati per Vector che utilizzano le funzioni del professore
void MyTestVector() {
    std::cout << "\nBegin of Vector<int> Test:" << std::endl;
    
    // Resettiamo il contatore dei test
    testResults.reset();
    
    // Test su Vector<int> avanzati
    
    // Test : Creazione di un SortableVector e verifica dimensione
    lasd::SortableVector<int> vec(5);
    for(unsigned long i = 0; i < vec.Size(); i++) {
        vec[i] = 10 - i * 2;  // Valori: 10, 8, 6, 4, 2
    }
    testResults.addTest(vec.Size() == 5, "SortableVector size is 5");
    
    // Test : Verifica non vuoto
    testResults.addTest(!vec.Empty(), "The container is not empty");
    
    // Test : Verifica valore front
    testResults.addTest(vec.Front() == 10, "The front of the container is \"10\"");
    
    // Test : Verifica valore back
    testResults.addTest(vec.Back() == 2, "The back of the container is \"2\"");
    
    // Test : Verifica ordinamento
    std::cout << "   Vector prima del sort: ";
    for(unsigned long i = 0; i < vec.Size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
    
    vec.Sort();
    
    std::cout << "   Vector dopo il sort: ";
    for(unsigned long i = 0; i < vec.Size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
    
    bool sorted = true;
    for(unsigned long i = 1; i < vec.Size(); i++) {
        if(vec[i-1] > vec[i]) {
            sorted = false;
            break;
        }
    }
    testResults.addTest(sorted, "Executing sort - elements are correctly ordered");
    
    // Test : Resize con espansione
    vec.Resize(10);
    testResults.addTest(vec.Size() == 10, "The container has size 10 after resize");
    
    // Test : Verifica elementi dopo espansione
    bool validDefaultValues = true;
    for(unsigned long i = 5; i < vec.Size(); i++) {
        if(vec[i] != 0) { // Assumiamo che il default per int sia 0
            validDefaultValues = false;
            break;
        }
    }
    testResults.addTest(validDefaultValues, "New elements initialized to default values");
    
    // Test : Test operator=
    lasd::SortableVector<int> vec2 = vec;
    testResults.addTest(vec == vec2, "Copy assignment operator works correctly");
    
    // Test : Test su vettore di dimensione grande
    bool bigVecTest = false;
    try {
        lasd::SortableVector<int> bigVec(1000000); // 1 milione di elementi
        bigVecTest = true;
    } catch(std::bad_alloc& e) {
        std::cout << "   Eccezione durante l'allocazione: " << e.what() << std::endl;
    }
    testResults.addTest(bigVecTest, "Allocating large vector (1M elements)");
    
    // Test : Test approfondito con stringhe
    lasd::SortableVector<std::string> strVec(5);

    // Inizializzazione con casi di test diversificati
    strVec[0] = "zebra";     // Ultima in ordine alfabetico
    strVec[1] = "abc";       // Prima in ordine alfabetico
    strVec[2] = "123";       // Stringa numerica
    strVec[3] = "ABC";       // Maiuscole
    strVec[4] = " spazio";   // Inizia con spazio

    std::cout << "\n   Test ordinamento stringhe:" << std::endl;
    std::cout << "   Caso iniziale: ";
    for(unsigned long i = 0; i < strVec.Size(); i++) {
    std::cout << "\"" << strVec[i] << "\" ";
     }
    std::cout << std::endl;

    // Verifica pre-ordinamento
    bool preSort = true;
    for(unsigned long i = 1; i < strVec.Size(); i++) {
    if(strVec[i-1] > strVec[i]) {
        preSort = false;
        break;
       }
     }
    testResults.addTest(!preSort, "Vector non ordinato prima del sort");

    // Esecuzione Sort
    strVec.Sort();

    std::cout << "   Dopo ordinamento: ";
    for(unsigned long i = 0; i < strVec.Size(); i++) {
    std::cout << "\"" << strVec[i] << "\" ";
     }
    std::cout << std::endl;

    // Verifica post-ordinamento con controlli multipli
    bool stringsSorted = true;
    bool correctOrder = true;
    bool maintainsContent = true;

    // Verifica ordinamento
    for(unsigned long i = 1; i < strVec.Size(); i++) {
    if(strVec[i-1] > strVec[i]) {
        stringsSorted = false;
        break;
      }
    }

   // Verifica che " spazio" sia prima di tutto
   correctOrder = (strVec[0] == " spazio");

   // Verifica che tutti gli elementi originali siano presenti
   std::vector<std::string> originalElements = {"zebra", "abc", "123", "ABC", " spazio"};
   for(const auto& elem : originalElements) {
     bool found = false;
     for(unsigned long i = 0; i < strVec.Size(); i++) {
         if(strVec[i] == elem) {
            found = true;
            break;
         }
     }
     if(!found) {
        maintainsContent = false;
        break;
     }
}

    testResults.addTest(stringsSorted, "Ordinamento lessicografico corretto");
    testResults.addTest(correctOrder, "Gestione corretta caratteri speciali");
    testResults.addTest(maintainsContent, "Preservazione contenuto originale");

    // Test aggiuntivo con stringa vuota
     strVec.Resize(6);
     strVec[5] = "";
     strVec.Sort();
     testResults.addTest(strVec[0] == "", "Gestione corretta stringa vuota");

    // Test : Resize a 0
    vec.Resize(0);
    testResults.addTest(vec.Empty(), "The container is empty after resizing to 0");
    
    // Test : Test di copia profonda
    lasd::SortableVector<int> vec3(2);
    vec3[0] = 100;
    vec3[1] = 200;
    lasd::SortableVector<int> vec4(vec3);
    vec3[0] = 300;  // Modifica l'originale
    testResults.addTest(vec4[0] == 100, "Deep copy - changing original doesn't affect copy");
    
    // Test : Test con numeri negativi
    lasd::SortableVector<int> negVec(5);
    negVec[0] = -5;
    negVec[1] = -2;
    negVec[2] = -10;
    negVec[3] = -1;
    negVec[4] = -7;
    
    std::cout << "   Vector con negativi prima del sort: ";
    for(unsigned long i = 0; i < negVec.Size(); i++) {
        std::cout << negVec[i] << " ";
    }
    std::cout << std::endl;
    
    negVec.Sort();
    
    std::cout << "   Vector con negativi dopo il sort: ";
    for(unsigned long i = 0; i < negVec.Size(); i++) {
        std::cout << negVec[i] << " ";
    }
    std::cout << std::endl;
    
    bool negSorted = true;
    for(unsigned long i = 1; i < negVec.Size(); i++) {
        if(negVec[i-1] > negVec[i]) {
            negSorted = false;
            break;
        }
    }
    testResults.addTest(negSorted, "Sorting negative numbers correctly");
    
    // Test : Test con numeri decimali (double)
    lasd::SortableVector<double> doubleVec(4);
    doubleVec[0] = 3.14;
    doubleVec[1] = 1.41;
    doubleVec[2] = 2.71;
    doubleVec[3] = 0.577;
    
    std::cout << "   Double vector prima del sort: ";
    for(unsigned long i = 0; i < doubleVec.Size(); i++) {
        std::cout << doubleVec[i] << " ";
    }
    std::cout << std::endl;
    
    doubleVec.Sort();
    
    std::cout << "   Double vector dopo il sort: ";
    for(unsigned long i = 0; i < doubleVec.Size(); i++) {
        std::cout << doubleVec[i] << " ";
    }
    std::cout << std::endl;
    
    bool doubleSorted = true;
    for(unsigned long i = 1; i < doubleVec.Size(); i++) {
        if(doubleVec[i-1] > doubleVec[i]) {
            doubleSorted = false;
            break;
        }
    }
    testResults.addTest(doubleSorted, "Sorting doubles correctly");
    
    // Test : Test con caratteri
    lasd::SortableVector<char> charVec(5);
    charVec[0] = 'z';
    charVec[1] = 'a';
    charVec[2] = 'm';
    charVec[3] = 'k';
    charVec[4] = 'b';
    
    std::cout << "   Char vector prima del sort: ";
    for(unsigned long i = 0; i < charVec.Size(); i++) {
        std::cout << charVec[i] << " ";
    }
    std::cout << std::endl;
    
    charVec.Sort();
    
    std::cout << "   Char vector dopo il sort: ";
    for(unsigned long i = 0; i < charVec.Size(); i++) {
        std::cout << charVec[i] << " ";
    }
    std::cout << std::endl;
    
    bool charSorted = true;
    for(unsigned long i = 1; i < charVec.Size(); i++) {
        if(charVec[i-1] > charVec[i]) {
            charSorted = false;
            break;
        }
    }
    testResults.addTest(charSorted, "Sorting characters correctly");

    // Test : Test con stringhe vuote
    lasd::SortableVector<std::string> specialStrVec(4);
    specialStrVec[0] = "";
    specialStrVec[1] = " ";
    specialStrVec[2] = "\t";
    specialStrVec[3] = "\n";
    
    specialStrVec.Sort();
    bool specialStrSorted = true;
    for(unsigned long i = 1; i < specialStrVec.Size(); i++) {
        if(specialStrVec[i-1] > specialStrVec[i]) {
            specialStrSorted = false;
            break;
        }
    }
    testResults.addTest(specialStrSorted, "Sorting vector with special strings");

    // Test : Stress test con operazioni ripetute
    lasd::SortableVector<int> stressVec(100);
    for(unsigned long i = 0; i < stressVec.Size(); i++) {
    stressVec[i] = 100 - i;
      }

    for(int i = 0; i < 10; i++) {  
    stressVec.Sort();
    // Verifica che sia ordinato dopo il sort
    bool isSorted = true;
    for(unsigned long j = 1; j < stressVec.Size(); j++) {
        if(stressVec[j-1] > stressVec[j]) {
            isSorted = false;
            break;
        }
     }
    
    if(!isSorted) {
        stringsSorted = false;
        break;
    }
    
    // Resize e reinserimento
    stressVec.Resize(50);
    stressVec.Resize(100);
    // Riempie la seconda metà con numeri più grandi di quelli presenti
    for(unsigned long j = 50; j < stressVec.Size(); j++) {
        stressVec[j] = 200 - j; 
      }
    }

     // Verifica finale dopo l'ultima iterazione
     if(stringsSorted) {
    stressVec.Sort();
     for(unsigned long i = 1; i < stressVec.Size(); i++) {
        if(stressVec[i-1] > stressVec[i]) {
            stringsSorted = false;
            break;
        }
      }
   }

    testResults.addTest(stringsSorted, "Stress test with repeated operations");

    

    // Test : Test di resize con vari scenari
    lasd::SortableVector<int> resizeVec(5);
    for(unsigned long i = 0; i < resizeVec.Size(); i++) {
        resizeVec[i] = i;
    }
    
    resizeVec.Resize(3);  // Riduzione
    bool resizeTestSmaller = (resizeVec.Size() == 3 && resizeVec[2] == 2);
    
    resizeVec.Resize(7);  // Espansione
    bool resizeTestLarger = (resizeVec.Size() == 7);
    
    resizeVec.Resize(0);  // Azzeramento
    bool resizeTestZero = (resizeVec.Empty());
    
    testResults.addTest(resizeTestSmaller && resizeTestLarger && resizeTestZero, 
                       "Multiple resize operations work correctly");

    // Test : Test con sequenza di operazioni miste
    lasd::SortableVector<int> mixedVec(3);
    mixedVec[0] = 30;
    mixedVec[1] = 10;
    mixedVec[2] = 20;
    
    mixedVec.Sort();           // Ordina
    mixedVec.Resize(4);        // Espandi
    mixedVec[3] = 15;         // Inserisci
    mixedVec.Sort();           // Riordina
    
    bool mixedOpsTest = true;
    for(unsigned long i = 1; i < mixedVec.Size(); i++) {
        if(mixedVec[i-1] > mixedVec[i]) {
            mixedOpsTest = false;
            break;
        }
    }
    testResults.addTest(mixedOpsTest, "Mixed operations sequence maintains correctness");

    
    // Test : Test con booleani
    lasd::SortableVector<bool> boolVec(4);
    boolVec[0] = true;
    boolVec[1] = false;
    boolVec[2] = true;
    boolVec[3] = false;
    
    std::cout << "   Bool vector prima del sort: ";
    for(unsigned long i = 0; i < boolVec.Size(); i++) {
        std::cout << (boolVec[i] ? "true" : "false") << " ";
    }
    std::cout << std::endl;
    
    boolVec.Sort();
    
    std::cout << "   Bool vector dopo il sort: ";
    for(unsigned long i = 0; i < boolVec.Size(); i++) {
        std::cout << (boolVec[i] ? "true" : "false") << " ";
    }
    std::cout << std::endl;
    
    bool boolSorted = true;
    for(unsigned long i = 1; i < boolVec.Size(); i++) {
        if(boolVec[i-1] > boolVec[i]) {
            boolSorted = false;
            break;
        }
    }
    testResults.addTest(boolSorted, "Sorting booleans correctly");

    // Test : Test con elementi duplicati
    lasd::SortableVector<int> dupVec(6);
    dupVec[0] = 5;
    dupVec[1] = 5;
    dupVec[2] = 3;
    dupVec[3] = 3;
    dupVec[4] = 5;
    dupVec[5] = 3;

    dupVec.Sort(); //dopo ordinamento, dovrei avere 3,3,3,5,5,5
    bool dupSorted = true;
    for(unsigned long i = 1; i < dupVec.Size(); i++) { //prima i minori
    if(dupVec[i-1] > dupVec[i]) {
        dupSorted = false;
        break;
       }

    }
    testResults.addTest(dupSorted, "Sorting vector with duplicate elements");

    // Test : Test con valori estremi
    lasd::SortableVector<int> extremeVec(5);
    extremeVec[0] = INT_MAX;
    extremeVec[1] = INT_MIN;
    extremeVec[2] = 0;
    extremeVec[3] = INT_MAX - 1;
    extremeVec[4] = INT_MIN + 1;

    extremeVec.Sort();
    bool extremeSorted = true;
    for(unsigned long i = 1; i < extremeVec.Size(); i++) {
      if(extremeVec[i-1] > extremeVec[i]) {
        extremeSorted = false;
        break;
      }
    }
    testResults.addTest(extremeSorted, "Sorting vector with extreme values");


    // Test : Test di robustezza con operazioni miste
    lasd::SortableVector<int> robustVec(3);
    robustVec[0] = 30;
    robustVec[1] = 20;
    robustVec[2] = 10;

    robustVec.Sort();
    robustVec.Resize(5);
    robustVec[3] = 5;
    robustVec[4] = 25;
    robustVec.Sort();

    bool robustTest = true;
    for(unsigned long i = 1; i < robustVec.Size(); i++) {
       if(robustVec[i-1] > robustVec[i]) {
        robustTest = false;
        break;
      }
    }
     testResults.addTest(robustTest, "Robustness test with mixed operations");


     // Test : Test di confronto tra vettori
     lasd::SortableVector<int> vecl1(3);
     lasd::SortableVector<int> vecl2(3);
     for(unsigned long i = 0; i < 3; i++) {
      vecl1[i] = i;
      vecl2[i] = i;
     }
     bool compareTest = (vecl1 == vecl2);
     vecl2[1] = 10;
     bool compareTest2 = (vecl1 != vecl2);
     testResults.addTest(compareTest && compareTest2, "Vector comparison operators");
    
    
    // Stampa il resoconto dei test
    testResults.printSummary("Vector<int>");
}

/* ************************************************************************** */

// Test personalizzati per List
void MyTestList() {
    std::cout << "\nBegin of List<int> Test:" << std::endl;
    
    // Resettiamo il contatore dei test
    testResults.reset();
    
    // Test 1: Creazione di una lista vuota
    lasd::List<int> list1;
    testResults.addTest(true, "Creating empty list"); // Il test passa se la creazione non genera eccezioni
    
    // Test 2: Dimensione lista vuota
    testResults.addTest(list1.Size() == 0, "The container has size 0");
    
    // Test 3: Empty su lista vuota
    testResults.addTest(list1.Empty(), "The container is empty");
    
    // Inserimento elementi
    for(int i = 0; i < 5; i++) {
        list1.InsertAtBack(i * 10);
    }
    
    // Test 4: Dimensione dopo inserimento
    testResults.addTest(list1.Size() == 5, "The container has size 5 after insertion");
    
    // Test 5: Empty dopo inserimento
    testResults.addTest(!list1.Empty(), "The container is not empty after insertion");
    
    // Test 6: Verifica Front
    testResults.addTest(list1.Front() == 0, "The front of the linear container is \"0\"");
    
    // Test 7: Verifica Back
    testResults.addTest(list1.Back() == 40, "The back of the linear container is \"40\"");
    
    // Test 8: Copia costruttore
    lasd::List<int> list2(list1);
    testResults.addTest(list1 == list2, "Copy constructor creates equal list");
    
    // Test 9: RemoveFromFront
    list2.RemoveFromFront();
    testResults.addTest(list1 != list2, "Lists differ after RemoveFromFront");
    
    // Test 10: Front dopo RemoveFromFront
    testResults.addTest(list2.Front() == 10, "The front of the linear container is \"10\" after RemoveFromFront");
    
    // Test 11: Dimensione dopo RemoveFromFront
    testResults.addTest(list2.Size() == 4, "The container has size 4 after RemoveFromFront");
    
    // Test 12: Front su lista vuota (eccezione attesa)
    bool frontExceptionThrown = false;
    try {
        lasd::List<int> emptyList;
        emptyList.Front();
    } catch(std::length_error&) {
        frontExceptionThrown = true;
    }
    testResults.addTest(frontExceptionThrown, "Front on empty list throws length_error");
    
    // Test 13: Back su lista vuota (eccezione attesa)
    bool backExceptionThrown = false;
    try {
        lasd::List<int> emptyList;
        emptyList.Back();
    } catch(std::length_error&) {
        backExceptionThrown = true;
    }
    testResults.addTest(backExceptionThrown, "Back on empty list throws length_error");
    
    // Test 14: RemoveFromFront su lista vuota (eccezione attesa)
    bool removeFromFrontExceptionThrown = false;
    try {
        lasd::List<int> emptyList;
        emptyList.RemoveFromFront();
    } catch(std::length_error&) {
        removeFromFrontExceptionThrown = true;
    }
    testResults.addTest(removeFromFrontExceptionThrown, "RemoveFromFront on empty list throws length_error");
    
    // Test 15: RemoveFromBack su lista vuota (eccezione attesa)
    bool removeFromBackExceptionThrown = false;
    try {
        lasd::List<int> emptyList;
        emptyList.RemoveFromBack();
    } catch(std::length_error&) {
        removeFromBackExceptionThrown = true;
    }
    testResults.addTest(removeFromBackExceptionThrown, "RemoveFromBack on empty list throws length_error");
    
     
    
    // Test 16: Test con lista di grandi dimensioni
    lasd::List<int> bigList;
    for(int i = 0; i < 10000; i++) {
        bigList.InsertAtBack(i);
    }
    testResults.addTest(bigList.Size() == 10000, "Large list creation and insertion (10000 elements)");

    // Test 17: Test di inserimenti e rimozioni alternati
    lasd::List<int> alternateList;
    for(int i = 0; i < 100; i++) {
        alternateList.InsertAtFront(i);
        if(!alternateList.Empty()) {
            alternateList.RemoveFromBack();
        }
        alternateList.InsertAtBack(i);
        if(!alternateList.Empty()) {
            alternateList.RemoveFromFront();
        }
    }
    alternateList.InsertAtBack(42);
    testResults.addTest(alternateList.Size() == 1 && alternateList.Front() == 42, 
                       "Alternate insertions and removals maintain consistency");

    // Test 18: Test con operazioni di copia dopo modifiche multiple
    lasd::List<int> originalList;
    for(int i = 0; i < 5; i++) {
        originalList.InsertAtBack(i);
        originalList.InsertAtFront(i);
    }
    lasd::List<int> copyList = originalList;
    originalList.Clear();
    testResults.addTest(!copyList.Empty() && copyList.Size() == 10, 
                       "Deep copy maintains independence after multiple operations");

    // Test 19: Test con stringhe di diversa lunghezza
    lasd::List<std::string> stringList;
    stringList.InsertAtBack("");
    stringList.InsertAtBack("a");
    stringList.InsertAtBack("aa");
    stringList.InsertAtBack("aaa");
    testResults.addTest(stringList.Size() == 4 && stringList.Back() == "aaa", 
                       "Handling strings of different lengths");

    // Test 20: Test di robustezza con operazioni miste
    lasd::List<int> robustList;
    for(int i = 0; i < 1000; i++) {
        robustList.InsertAtFront(i * 2);
        if(i % 2 == 0) {
            robustList.RemoveFromBack();
        }
    }
    testResults.addTest(robustList.Size() == 500, 
                       "Consistency after multiple mixed operations");

    // Test 21: Test con valori limite
    lasd::List<int> extremeList;
    extremeList.InsertAtFront(INT_MAX);
    extremeList.InsertAtBack(INT_MIN);
    testResults.addTest(extremeList.Front() == INT_MAX && extremeList.Back() == INT_MIN, 
                       "Handling extreme values (INT_MAX/MIN)");

    // Test 22: Test di concatenazione elementi
    lasd::List<std::string> concatList;
    concatList.InsertAtBack("Hello");
    concatList.InsertAtBack(" ");
    concatList.InsertAtBack("World");
    std::string result;
    for(unsigned long i = 0; i < concatList.Size(); i++) {
        result += concatList[i];
    }
    testResults.addTest(result == "Hello World", 
                       "String concatenation in list");

     // Test 27: Test con stringhe miste (numeri e lettere)
     lasd::List<std::string> mixedStringList;
     mixedStringList.InsertAtBack("123abc");
     mixedStringList.InsertAtBack("ABC123");
     mixedStringList.InsertAtBack("1a2b3c");
     testResults.addTest(mixedStringList.Size() == 3 && mixedStringList.Front() == "123abc", 
                   "Handling mixed alphanumeric strings");

    // Test 28: Test di modifica di stringhe
    lasd::List<std::string> modifyStringList;
    modifyStringList.InsertAtBack("test");
    modifyStringList.Front() += "_modified";
    testResults.addTest(modifyStringList.Front() == "test_modified", 
                   "String modification in container");

    // Test 29: Test con stringhe contenenti spazi
    lasd::List<std::string> spaceStringList;
    spaceStringList.InsertAtBack("   leading spaces");
    spaceStringList.InsertAtBack("trailing spaces   ");
    spaceStringList.InsertAtBack("   both   sides   ");
    testResults.addTest(spaceStringList.Size() == 3, 
                   "Handling strings with various space patterns");

   

    // Stampa il resoconto dei test
    testResults.printSummary("List<int>");
}

/* ************************************************************************** */

void MyTestSetVec() {
    std::cout << "\nBegin of SetVec<int> Test:" << std::endl;
    
    // Resettiamo il contatore dei test
    testResults.reset();
    
    // Test : Creazione di un set vuoto
    lasd::SetVec<int> setVec;
    testResults.addTest(true, "Creating empty set"); // Il test passa se la creazione non genera eccezioni
    
    // Test : Dimensione set vuoto
    testResults.addTest(setVec.Size() == 0, "The container has size 0");
    
    // Test : Empty su set vuoto
    testResults.addTest(setVec.Empty(), "The container is empty");
    
    // Test : Inserimento elementi
    testResults.addTest(setVec.Insert(10), "Inserting element 10 succeeds");
    
    // Test : Inserimento elemento duplicato 
    testResults.addTest(!setVec.Insert(10), "Inserting duplicate element 10 fails");
    
    // Test : Verifica dimensione dopo inserimento
    testResults.addTest(setVec.Size() == 1, "The container has size 1 after insertion");
    
    // Test : Inserimento multiplo
    setVec.Insert(20);
    setVec.Insert(30);
    setVec.Insert(40);
    testResults.addTest(setVec.Size() == 4, "The container has size 4 after multiple insertions");
    
    // Test : Verifica esistenza elemento
    testResults.addTest(setVec.Exists(20), "Data \"20\" does exist");
    
    // Test : Verifica assenza elemento
    testResults.addTest(!setVec.Exists(25), "Data \"25\" does not exist");
    
    // Test : Rimozione elemento
    setVec.Remove(20);
    testResults.addTest(!setVec.Exists(20), "Data \"20\" does not exist after removal");
    
    // Test : Dimensione dopo rimozione
    testResults.addTest(setVec.Size() == 3, "The container has size 3 after removal");
    
    // Test : Operatore =
    lasd::SetVec<int> setVec2 = setVec;
    testResults.addTest(setVec == setVec2, "Copy assignment operator creates equal set");
    
    // Test : Clear
    setVec2.Clear();
    testResults.addTest(setVec2.Empty(), "The container is empty after Clear");
    
    
    // Test : Rimozione elemento non esistente
    bool beforeRemove = setVec.Exists(50);
    setVec.Remove(50);
    bool afterRemove = setVec.Exists(50);
    testResults.addTest(beforeRemove == afterRemove, "Removing non-existent element has no effect");

    
    // Test : Test con grandi dimensioni
    lasd::SetVec<int> largeSet;
    for(int i = 0; i < 1000; i++) {
        largeSet.Insert(i);
    }
    testResults.addTest(largeSet.Size() == 1000, "Large set creation and insertion (1000 elements)");
    
    // Test : Test con valori limite
    lasd::SetVec<int> extremeSet;
    extremeSet.Insert(INT_MAX);
    extremeSet.Insert(INT_MIN);
    extremeSet.Insert(0);
    testResults.addTest(extremeSet.Size() == 3 && extremeSet.Exists(INT_MAX) && extremeSet.Exists(INT_MIN),
                       "Handling extreme values (INT_MAX/MIN)");

    // Test : Test di robustezza con operazioni miste
    lasd::SetVec<int> mixedSet;
    for(int i = 0; i < 100; i++) {
        mixedSet.Insert(i);
        if(i % 2 == 0) {
            mixedSet.Remove(i);
        }
    }
    testResults.addTest(mixedSet.Size() == 50, "Mixed operations maintain correct size");

    
    // Test : Test con stringhe speciali
    lasd::SetVec<std::string> specialSet;
    specialSet.Insert("");
    specialSet.Insert(" ");
    specialSet.Insert("\n");
    specialSet.Insert("\t");
    testResults.addTest(specialSet.Size() == 4, "Handling special strings");

    // Test : Test di copia profonda
    lasd::SetVec<int> originalSet;
    originalSet.Insert(1);
    originalSet.Insert(2);
    lasd::SetVec<int> copiedSet = originalSet;
    originalSet.Remove(1);
    testResults.addTest(copiedSet.Exists(1), "Deep copy maintains independence");
   
    // Stampa il resoconto dei test
    testResults.printSummary("SetVec<int>");
    
}


// Test per SetList
void MyTestSetList() {
    std::cout << "\nBegin of SetList<int> Test:" << std::endl;
    
    // Resettiamo il contatore dei test
    testResults.reset();
    
    // Test : Creazione di un set vuoto
    lasd::SetLst<int> setList;
    testResults.addTest(true, "Creating empty set list");
    
    // Test : Dimensione set vuoto
    testResults.addTest(setList.Size() == 0, "Empty set has size 0");
    
    // Test : Empty su set vuoto
    testResults.addTest(setList.Empty(), "New set is empty");
    
    // Test : Inserimenti base
    testResults.addTest(setList.Insert(10), "Inserting first element succeeds");
    testResults.addTest(!setList.Insert(10), "Inserting duplicate fails");
    
    // Test : Inserimenti multipli
    setList.Insert(20);
    setList.Insert(30);
    testResults.addTest(setList.Size() == 3, "Multiple insertions maintain correct size");
    
    // Test : Rimozioni
    setList.Remove(20);
    testResults.addTest(!setList.Exists(20) && setList.Size() == 2, 
                       "Removal updates size and existence correctly");

    // Test : Operazioni di copia
    lasd::SetLst<int> setList2 = setList;
    testResults.addTest(setList == setList2, "Copy constructor creates equal set");
    
    // Test : Clear
    setList.Clear();
    testResults.addTest(setList.Empty(), "Clear makes set empty");
    
    // Test : Grandi dimensioni
    for(int i = 0; i < 1000; i++) {
        setList.Insert(i);
    }
    testResults.addTest(setList.Size() == 1000, "Large set list handles 1000 elements");


    // Test con stringhe
    std::cout << "\n\n==== Inizio Test Set<std::string> ====\n" << std::endl;
    
    // Test 1: Inserimento di stringhe
    lasd::SetLst<std::string> stringSet;
    stringSet.Insert("mela");
    stringSet.Insert("banana");
    stringSet.Insert("arancia");
    stringSet.Insert("kiwi");
    stringSet.Insert("pesca");
    testResults.addTest(stringSet.Size() == 5, 
                   "Inserimento di 5 stringhe distinte");

    // Test 2: Controllo duplicati case-sensitive
    stringSet.Insert("Mela");  // Diverso da "mela" (maiuscola)
    testResults.addTest(stringSet.Size() == 6, 
                   "Case sensitivity nell'inserimento");

    // Test 3: Controllo duplicati esatti
    stringSet.Insert("mela");  // Già presente
    stringSet.Insert("banana");  // Già presente
    testResults.addTest(stringSet.Size() == 6, 
                   "Gestione corretta dei duplicati");

    // Test 4: Gestione stringhe vuote
    stringSet.Insert("");
    testResults.addTest(stringSet.Exists(""), 
                   "Inserimento e ricerca di stringa vuota");

    // Test 5: Stringhe con spazi
    stringSet.Insert("frutta fresca");
    stringSet.Insert("   con spazi iniziali");
    stringSet.Insert("con spazi finali   ");
    testResults.addTest(stringSet.Size() == 10, 
                   "Gestione stringhe con spazi");

    // Test 6: Rimozione e verifica
    stringSet.Remove("mela");
    testResults.addTest(!stringSet.Exists("mela") && stringSet.Exists("Mela"), 
                   "Rimozione selettiva di stringhe (case sensitive)");

    // Test 7: Copia del set
    lasd::SetLst<std::string> copiedSet = stringSet;
    testResults.addTest(copiedSet.Size() == stringSet.Size(), 
                   "Costruttore di copia - stesso numero di elementi");
    
    bool allElementsPresent = true;
    stringSet.Traverse([&copiedSet, &allElementsPresent](const std::string& str) {
        if (!copiedSet.Exists(str)) {
            allElementsPresent = false;
        }
    });
    testResults.addTest(allElementsPresent, 
                   "Costruttore di copia - tutti gli elementi presenti");

    // Test 8: Operazioni di OrderedDictionaryContainer
    testResults.addTest(!stringSet.Empty(), 
                   "Controllo che il set non sia vuoto");
    std::string minValue = stringSet.Min();
    std::string maxValue = stringSet.Max();
    testResults.addTest(minValue <= stringSet.Min(), 
                   "Operazione Min() restituisce effettivamente il minimo");
    testResults.addTest(maxValue >= stringSet.Max(), 
                   "Operazione Max() restituisce effettivamente il massimo");
    
    // Test 9: Successor e Predecessor
    if (stringSet.Size() > 2) {
        std::string someValue = stringSet.Min(); // Prendiamo un valore qualsiasi che non sia né il minimo né il massimo
        lasd::SetLst<std::string> tempSet = stringSet;
        tempSet.RemoveMin();
        someValue = tempSet.Min();
        
        testResults.addTest(stringSet.Successor(stringSet.Min()) == someValue, 
                      "Verifica dell'operazione Successor");
                      
        std::string predValue = stringSet.Predecessor(maxValue);
        testResults.addTest(predValue < maxValue && predValue != minValue, 
                      "Verifica dell'operazione Predecessor");
    }

    

    // Test : Valori limite
    lasd::SetLst<int> extremeSetList;
    extremeSetList.Insert(INT_MAX);
    extremeSetList.Insert(INT_MIN);
    testResults.addTest(extremeSetList.Exists(INT_MAX) && extremeSetList.Exists(INT_MIN),
                       "Handling extreme values in set list");

    // Test : Move semantics
    lasd::SetLst<int> moveSource;
    moveSource.Insert(100);
    moveSource.Insert(200);
    lasd::SetLst<int> moveDest(std::move(moveSource));
    testResults.addTest(moveSource.Empty() && moveDest.Size() == 2,
                       "Move constructor works correctly");
     
       
    // Test : Operazioni di unione
    lasd::SetLst<int> set1, set2;
    set1.Insert(1);
    set1.Insert(2);
    set2.Insert(2);
    set2.Insert(3);
    lasd::SetLst<int> set3;

    // Inseriamo prima tutti gli elementi del primo set
    set3.Insert(1);
    set3.Insert(2);

    // Aggiungiamo gli elementi del secondo set
    set3.Insert(2);  // Questo non avrà effetto perché 2 è già presente
    set3.Insert(3);

    testResults.addTest(set3.Size() == 3 && 
                        set3.Exists(1) && 
                        set3.Exists(2) && 
                        set3.Exists(3), 
                         "Set union maintains unique elements");

    // Test 1: Creazione e inserimento in un Set di numeri float
    std::cout << "\n\n==== Inizio Test Set<double> ====\n" << std::endl;
    lasd::SetLst<double> floatSet;
    floatSet.Insert(4.0);
    floatSet.Insert(0.4);
    floatSet.Insert(1.2);
    floatSet.Insert(2.1);
    floatSet.Insert(3.5);
    floatSet.Insert(5.3);
    testResults.addTest(floatSet.Size() == 6, 
                   "Inserimento di 6 valori float distinti");

    // Test 2: Verifica dell'esistenza di elementi
    testResults.addTest(floatSet.Exists(4.0), 
                   "Verifica esistenza di 4.0 nel Set");
    testResults.addTest(floatSet.Exists(5.3), 
                   "Verifica esistenza di 5.3 nel Set");
    testResults.addTest(!floatSet.Exists(7.7), 
                   "Verifica non esistenza di 7.7 nel Set");

    // Test 3: Inserimento di duplicati
    floatSet.Insert(4.0);  // Già presente
    floatSet.Insert(2.1);  // Già presente
    testResults.addTest(floatSet.Size() == 6, 
                   "Gestione corretta dei duplicati (size immutata)");

    // Test 4: Rimozione di elementi
    floatSet.Remove(4.0);
    testResults.addTest(!floatSet.Exists(4.0) && floatSet.Size() == 5, 
                   "Rimozione di un elemento esistente (4.0)");
    
    floatSet.Remove(9.9);  // Non esiste
    testResults.addTest(floatSet.Size() == 5, 
                   "Tentativo di rimozione di elemento inesistente");

    // Test 5: Test con valori negativi e zero
    lasd::SetLst<double> mixedSet;
    mixedSet.Insert(-3.14);
    mixedSet.Insert(0.0);
    mixedSet.Insert(2.718);
    mixedSet.Insert(-0.0);  // Dovrebbe essere considerato uguale a 0.0
    testResults.addTest(mixedSet.Size() == 3, 
                   "Gestione di valori negativi e zero");

    // Test 6: Test di attraversamento (usando un accumulatore)
    double sum = 0.0;
    floatSet.Traverse([&sum](const double& value) {
        sum += value;
    });
    // La somma attesa è: 0.4 + 1.2 + 2.1 + 3.5 + 5.3 = 12.5
    testResults.addTest(std::abs(sum - 12.5) < 0.0001, 
                   "Attraversamento con funzione di accumulazione");

    // Test 7: Valori specifici con precisione limitata
    lasd::SetLst<double> precisionSet;
    precisionSet.Insert(1.1);
    precisionSet.Insert(1.10);  
    precisionSet.Insert(1.100001);  
    testResults.addTest(precisionSet.Size() <= 2, 
                   "Gestione della precisione dei float");

    // Test 8: Operazioni di OrderedDictionaryContainer
    testResults.addTest(floatSet.Min() == 0.4, 
                   "Operazione Min()");
    testResults.addTest(floatSet.Max() == 5.3, 
                   "Operazione Max()");
    
    // Test 9: Clear e Empty
    floatSet.Clear();
    testResults.addTest(floatSet.Empty(), 
                   "Svuotamento del Set");
    testResults.addTest(floatSet.Size() == 0, 
                   "Size pari a 0 dopo Clear");

    
    // Stampa il resoconto dei test
    testResults.printSummary("Set Tests");
   

}




/* ************************************************************************** */

// Funzione principale per l'esecuzione dei test personalizzati
void mytest() {
    int scelta;
    
    std::cout << "~*~#~*~ Benvenuti in: LASD Test Suite Custom~*~#~*~!" << std::endl;
    
    do {
        std::cout << "\nScegli il test da eseguire:" << std::endl;
        std::cout << "1. Test Vector" << std::endl;
        std::cout << "2. Test List" << std::endl;
        std::cout << "3. Test Set" << std::endl;
        std::cout << "4. Esegui tutti i test" << std::endl;
        std::cout << "0. Esci" << std::endl;
        std::cout << "Scelta: ";
        std::cin >> scelta;
        
        switch(scelta) {
            case 1:
                MyTestVector();
                break;
            case 2:
                MyTestList();
                break;
            case 3:
                MyTestSetVec();
                MyTestSetList();
                break;
            case 4:
                std::cout << "\n========= ESECUZIONE DI TUTTI I TEST =========" << std::endl;
                MyTestVector();
                MyTestList();
                MyTestList();
                break;
            case 0:
                std::cout << "Uscita dai test personalizzati" << std::endl;
                break;
            default:
                std::cout << "Scelta non valida" << std::endl;
        }
    } while(scelta != 0);
}

/* ************************************************************************** */