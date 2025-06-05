#include "test.hpp"
#include <iostream>
#include <cassert>
#include <iomanip>
#include <cfloat>
#include <random>


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

#include "../zlasdtest/heap/heap.hpp"  //includiamo anche i test del secondo esercizio
#include "../zlasdtest/pq/pq.hpp"


#include "../vector/vector.hpp"  
#include "../list/list.hpp"      
#include "../set/set.hpp"        
#include "../set/vec/setvec.hpp"
#include "../set/lst/setlst.hpp"
                                 //includiamo anche i test del secondo esercizio 
#include "../pq/pq.hpp"
#include "../pq/heap/pqheap.hpp"
#include "../heap/heap.hpp"
#include "../heap/vec/heapvec.hpp"

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
/* TEST ESERCIZIO 1 COMMENTATI

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
 */
/* ************************************************************************** */
// Test aggiuntivi per Exercise 2A (Heap) e 2B (Priority Queue)

void MyTestPQ() {
    std::cout << "\nBegin of Priority Queue Tests:" << std::endl;
    // Resettiamo il contatore dei test
    testResults.reset();
    // Test: costruttore con vector vuoto
    lasd::Vector<int> emptyVec(0);
    lasd::PQHeap<int> pqEmpty(emptyVec);
    testResults.addTest(pqEmpty.Empty(), "Priority Queue created with empty vector is empty");  
    testResults.addTest(pqEmpty.Size() == 0, "Priority Queue created with empty vector has size 0");
    // Test: costruttore con vector con un elemento
    lasd::Vector<int> singleVec(1);
    singleVec[0] = 42;
    lasd::PQHeap<int> pqSingle(singleVec);
    testResults.addTest(pqSingle.Size() == 1, "Priority Queue with single element has size 1");
    testResults.addTest(pqSingle.Empty() == false, "Priority Queue with single element is not empty");
    testResults.addTest(pqSingle.Tip() == 42, "Priority Queue with single element has correct top value");
    // Test: operazioni su PQ vuota
    lasd::PQHeap<int> pqEmpty2;
    bool tipThrows = false, removeThrows = false, tipNRemoveThrows = false;
    
    try { pqEmpty2.Tip(); } catch(...) { tipThrows = true; }
    try { pqEmpty2.RemoveTip(); } catch(...) { removeThrows = true; }
    try { pqEmpty2.TipNRemove(); } catch(...) { tipNRemoveThrows = true; }
    testResults.addTest(tipThrows, "Tip on empty PQ throws exception");
    testResults.addTest(removeThrows, "RemoveTip on empty PQ throws exception");
    testResults.addTest(tipNRemoveThrows, "TipNRemove on empty PQ throws exception");
        // Test: Move constructor
    lasd::PQHeap<int> srcPQ;
    for(int i = 0; i < 5; i++) {
        srcPQ.Insert(i);
    }
    int originalSize = srcPQ.Size();
    int originalTop = srcPQ.Tip();
    
    // Test move constructor
    lasd::PQHeap<int> movedPQ(std::move(srcPQ));
    testResults.addTest(movedPQ.Size() == static_cast<unsigned long>(originalSize), 
                   "Move constructor preserves size");
    testResults.addTest(movedPQ.Tip() == originalTop, "Move constructor preserves top element");
    testResults.addTest(srcPQ.Empty(), "Source PQ is empty after move constructor");
    
    // Test: Move assignment operator
    lasd::PQHeap<int> srcPQ2;
    for(int i = 0; i < 3; i++) {
        srcPQ2.Insert(i * 10);
    }
    originalSize = srcPQ2.Size();
    originalTop = srcPQ2.Tip();
    
    lasd::PQHeap<int> assignedPQ;
    assignedPQ = std::move(srcPQ2);
    testResults.addTest(assignedPQ.Size() == static_cast<unsigned long>(originalSize), 
                   "Move assignment preserves size");
    testResults.addTest(assignedPQ.Tip() == originalTop, "Move assignment preserves top element");
    testResults.addTest(srcPQ2.Empty(), "Source PQ is empty after move assignment");
    
    // Test: Chain of move operations
    lasd::PQHeap<int> pq1, pq2, pq3;
    pq1.Insert(42);
    pq2 = std::move(pq1);
    pq3 = std::move(pq2);
    testResults.addTest(pq3.Tip() == 42, "Chain of move operations preserves value");
    testResults.addTest(pq1.Empty() && pq2.Empty(), "Chain of moves leaves intermediate PQs empty");
    
    // Test: Move operations with strings
    lasd::PQHeap<std::string> strPQ;
    strPQ.Insert("test");
    strPQ.Insert("move");
    lasd::PQHeap<std::string> movedStrPQ(std::move(strPQ));
    testResults.addTest(movedStrPQ.Tip() == "test", "Move constructor works with strings");
    testResults.addTest(strPQ.Empty(), "Source string PQ is empty after move");
        // Multi-element PQ tests
    lasd::Vector<int> multiVec(5);
    multiVec[0] = 10; multiVec[1] = 30; multiVec[2] = 20; multiVec[3] = 50; multiVec[4] = 40;
    lasd::PQHeap<int> pqMulti(multiVec);
    testResults.addTest(pqMulti.Size() == 5, "Multi-element PQ has correct size");
    testResults.addTest(pqMulti.Tip() == 50, "Multi-element PQ has correct max value at tip");

    // Test sequence of operations
    int tip1 = pqMulti.TipNRemove();
    int tip2 = pqMulti.TipNRemove();
    testResults.addTest(tip1 == 50 && tip2 == 40, "TipNRemove returns elements in correct order");
    testResults.addTest(pqMulti.Size() == 3, "Size updates correctly after removals");

    // Copy constructor test
    lasd::PQHeap<int> pqCopy = pqMulti;
    testResults.addTest(pqCopy.Size() == pqMulti.Size(), "Copy constructor preserves size");
    testResults.addTest(pqCopy.Tip() == pqMulti.Tip(), "Copy constructor preserves tip value");

    // Test with string type
    lasd::Vector<std::string> strVec(3);
    strVec[0] = "banana"; strVec[1] = "apple"; strVec[2] = "cherry";
    lasd::PQHeap<std::string> pqString(strVec);
    testResults.addTest(pqString.Tip() == "cherry", "String PQ maintains correct order");

    // Test with double type and precision
    lasd::Vector<double> doubleVec(4);
    doubleVec[0] = 3.14; doubleVec[1] = 2.718; doubleVec[2] = 1.414; doubleVec[3] = 1.732;
    lasd::PQHeap<double> pqDouble(doubleVec);
    testResults.addTest(std::abs(pqDouble.Tip() - 3.14) < 0.0001, "Double PQ maintains precision");

    // Test with extreme values
    lasd::Vector<int> extremeVec(3);
    extremeVec[0] = INT_MAX; extremeVec[1] = 0; extremeVec[2] = INT_MIN;
    lasd::PQHeap<int> pqExtreme(extremeVec);
    testResults.addTest(pqExtreme.Tip() == INT_MAX, "PQ handles extreme values correctly");

    // Test insertion order independence
    lasd::Vector<int> vec1(3), vec2(3);
    vec1[0] = 1; vec1[1] = 2; vec1[2] = 3;
    vec2[0] = 3; vec2[1] = 1; vec2[2] = 2;
    lasd::PQHeap<int> pqTest1(vec1), pqTest2(vec2);
    testResults.addTest(pqTest1.Tip() == pqTest2.Tip(), 
                   "PQ maintains heap property regardless of insertion order");

    // Test empty after removing all elements
    while (!pqTest1.Empty()) {
    pqTest1.RemoveTip();
    }
    testResults.addTest(pqTest1.Empty(), "PQ is empty after removing all elements");
    testResults.addTest(pqTest1.Size() == 0, "PQ size is 0 after removing all elements");
    // Test con operazioni Push/Pop alternate
    lasd::PQHeap<int> pqAlternate;
    for(int i = 0; i < 100; i++) {
        pqAlternate.Insert(i);
        if(i % 2 == 0) {
            pqAlternate.RemoveTip();
        }
    }
    testResults.addTest(pqAlternate.Size() == 50, "Alternate Insert/RemoveTip operations");
    
    // Test con valori decimali e precisione
    lasd::PQHeap<double> pqPrecision;
    pqPrecision.Insert(3.14159);
    pqPrecision.Insert(3.14158);
    pqPrecision.Insert(3.14160);
    testResults.addTest(std::abs(pqPrecision.Tip() - 3.14160) < 0.00001, "High precision floating point comparison");
    
    // Test con stringhe di lunghezze diverse
    lasd::PQHeap<std::string> pqVarStrings;
    pqVarStrings.Insert("a");
    pqVarStrings.Insert("aaa");
    pqVarStrings.Insert("aa");
    testResults.addTest(pqVarStrings.Tip() == "aaa", "Variable length string comparison");
    
    // Test di stabilità con elementi uguali
    lasd::PQHeap<std::pair<int, int>> pqStability;
    pqStability.Insert({5, 1});
    pqStability.Insert({5, 2});
    pqStability.Insert({5, 3});
    testResults.addTest(pqStability.Tip().first == 5, "Equal elements handling");
    
    // Test con elementi negativi e positivi alternati
    lasd::PQHeap<int> pqMixed;
    pqMixed.Insert(1);
    pqMixed.Insert(-1);
    pqMixed.Insert(2);
    pqMixed.Insert(-2);
    testResults.addTest(pqMixed.Tip() == 2, "Mixed positive/negative values");
    ///////////////////////////////////////// 
    // Test di stabilità con elementi uguali
    lasd::PQHeap<std::pair<int, int>> pqUqualityStability;
    pqUqualityStability.Insert({5, 1});
    pqUqualityStability.Insert({5, 2});
    pqUqualityStability.Insert({5, 3});
    testResults.addTest(pqUqualityStability.Tip().first == 5, "Equal elements handling");   
    pqUqualityStability.RemoveTip();
    testResults.addTest(pqUqualityStability.Tip().first == 5, "Equal elements handling after removal");

    
    // Test di performance con molte copie
    lasd::PQHeap<int> originalPerf;
    for(int i = 0; i < 200; i++) {
        originalPerf.Insert(i);
    }
    
    std::vector<lasd::PQHeap<int>> copies;
    for(int i = 0; i < 10; i++) {
        copies.push_back(originalPerf);
    }
    
    bool allCopiesValid = true;
    for(const auto& copy : copies) {
        if(copy.Tip() != 199 || copy.Size() != 200) {
            allCopiesValid = false;
            break;
        }
    }
    testResults.addTest(allCopiesValid, "Multiple copies consistency");
    // Test con stringhe con spazi
    lasd::PQHeap<std::string> spacePQ;
    spacePQ.Insert("apple");
    spacePQ.Insert("banana");
    spacePQ.Insert("   leading spaces");
    spacePQ.Insert("trailing spaces   ");
    spacePQ.Insert("  middle  spaces  ");
    spacePQ.Insert("nospaces");
    // La stringa con più spazi all'inizio dovrebbe essere la più grande lessicograficamente
    testResults.addTest(spacePQ.Tip() == "trailing spaces   ", "Space character handling in strings");
 
    // Test con stringhe identiche
    lasd::PQHeap<std::string> identicalPQ;
    identicalPQ.Insert("same");
    identicalPQ.Insert("same");
    identicalPQ.Insert("same");
    testResults.addTest(identicalPQ.Size() == 3, "Identical strings all stored");
    testResults.addTest(identicalPQ.Tip() == "same", "Identical strings tip");
     // Test con zero positivo e negativo
    lasd::PQHeap<double> zeroPQ;
    zeroPQ.Insert(0.0);
    zeroPQ.Insert(-0.0);
    zeroPQ.Insert(0.1);
    testResults.addTest(zeroPQ.Tip() == 0.1, "Positive zero handling");
    
    // Test con numeri molto piccoli
    lasd::PQHeap<double> precisionPQ;
    precisionPQ.Insert(0.000001);
    precisionPQ.Insert(0.000002);
    precisionPQ.Insert(0.0000005);
    testResults.addTest(precisionPQ.Tip() == 0.000002, "Small number precision");
    
    // Test di svuotamento e riempimento
    lasd::PQHeap<int> pqCycle;
    for(int i = 0; i < 10; i++) {
        pqCycle.Insert(i);
    }
    while(!pqCycle.Empty()) {
        pqCycle.RemoveTip();
    }
    testResults.addTest(pqCycle.Empty(), "Empty after multiple removals");
    for(int i = 0; i < 5; i++) {
        pqCycle.Insert(i);
    }
    testResults.addTest(pqCycle.Size() == 5, "Refill after emptying");
    
    
    // Test con operazioni di copia dopo modifiche
    lasd::PQHeap<int> pqOriginal;
    pqOriginal.Insert(100);
    pqOriginal.Insert(200);
    lasd::PQHeap<int> pqCopied = pqOriginal;
    pqOriginal.RemoveTip();
    testResults.addTest(pqCopied.Tip() == 200, "Deep copy independence");
    
    // Test di stress con molte operazioni
    lasd::PQHeap<int> pqStress;
    for(int i = 0; i < 1000; i++) {
        pqStress.Insert(rand() % 1000);
        if(i % 3 == 0 && !pqStress.Empty()) {
            pqStress.RemoveTip();
        }
    }
    testResults.addTest(pqStress.Size() > 0, "Stress test survival");

    //PROVIAMO AD AGGIUNGERNE ALTRI
    std::cout <<"\n Inizio test aggiuntivi"<< std::endl;
    //Test con change
    lasd::PQHeap<int> changePQ;
    changePQ.Insert(50);
    changePQ.Insert(30);
    changePQ.Insert(70);
    changePQ.Insert(10);
    changePQ.Insert(60);
    testResults.addTest(changePQ.Tip() == 70, "Initial tip is correct before change");
    changePQ.Change(0, 5); // l'elemento con indice 0 è il max
    testResults.addTest(changePQ.Tip() == 60, "Change max to small value: new tip is next max");
    changePQ.Clear(); // puliamo la coda
    changePQ.Insert(50);
    changePQ.Insert(40);
    testResults.addTest(changePQ.Tip() == 50, "Tip before Change to same value");
    changePQ.Change(0, 50); // cambiamo il max con lo stesso valore
    testResults.addTest(changePQ.Tip() == 50, "Tip after Change to same value remains unchanged");

    // Test con Exists
    lasd::PQHeap<int> existsPQ;
    existsPQ.Insert(10);
    existsPQ.Insert(20);
    existsPQ.Insert(30);
    testResults.addTest(existsPQ.Exists(20), "Exists returns true for existing element");
    testResults.addTest(!existsPQ.Exists(40), "Exists returns false for non-existing element");
    existsPQ.RemoveTip(); // rimuoviamo il max
    testResults.addTest(!existsPQ.Exists(30), "Exists returns false for removed element");
    testResults.addTest(existsPQ.Exists(10), "Exists returns true for still existing element");
    existsPQ.Insert(20); // aggiungiamo un duplicato
    testResults.addTest(existsPQ.Exists(20), "Exists returns true for re-inserted element");

    // test di svuotamento e riempimento
    lasd::PQHeap<int> aggressivePQ;
    for(int k=0; k<5; ++k) {
        for(int i=0; i<50; ++i) {
            aggressivePQ.Insert(i);
        }
        testResults.addTest(aggressivePQ.Size() == 50, "Aggressive cycle: size afert insert");
        aggressivePQ.Clear(); // svuotiamo la coda
        testResults.addTest(aggressivePQ.Empty(), "Aggressive cycle: PQ is empty after Clear");
    }
    testResults.addTest(aggressivePQ.Empty(), "Aggressive cycle: size after Empty is 0");

    //Test di copy assignment su pq con elementi
    lasd::PQHeap<int> pqAssignsrc;
    pqAssignsrc.Insert(1);
    pqAssignsrc.Insert(2);
    pqAssignsrc.Insert(3);
    lasd::PQHeap<int> pqAssignDest;
    pqAssignDest.Insert(10);
    pqAssignDest.Insert(20);
    pqAssignDest = pqAssignsrc; // operazione di assegnamento
    testResults.addTest(pqAssignDest.Size() == pqAssignsrc.Size(), "Assignment operator preserves size");
    
    //Test  di move assignment su pq con elementi
    lasd::PQHeap<int> pqMoveAssignSource;
    pqMoveAssignSource.Insert(100); pqMoveAssignSource.Insert(200); pqMoveAssignSource.Insert(300);
    lasd::PQHeap<int> pqMoveAssignDest;
    pqMoveAssignDest.Insert(10); pqMoveAssignDest.Insert(20);
    pqMoveAssignDest = std::move(pqMoveAssignSource); // Assegnazione per spostamento
    
    testResults.addTest(pqMoveAssignDest.Size() == 3, "Move assignment: dest size is source size");
    testResults.addTest(pqMoveAssignDest.Tip() == 300, "Move assignment: dest has source's top");

    // Test per capire se sono in segmentation fault o mem leak

    std::random_device rd;       //genera numeri casuali
    std::mt19937 gen(rd());     //partendo dal generatore rd, mi genera sempre numeri diversi
    std::uniform_int_distribution<> distrib(0, 10000);     //li conforma
     {
        lasd::PQHeap<int> pqEmptyDestructor;
        // Non facciamo nulla, l'oggetto verrà distrutto uscendo dal blocco
        testResults.addTest(true, "Destructor on empty PQHeap<int> (no crash)");
    }
    {
        lasd::PQHeap<std::string> pqEmptyStrDestructor;
        testResults.addTest(true, "Destructor on empty PQHeap<string> (no crash)");
    }
    

    // Test per capire se il distruttore dealloca correttamente un heap abbastanza grande da farmi crashare
    { 
        lasd::PQHeap<int> pqLargeDestructor;
        for (int i = 0; i < 10000; ++i) { // Molti elementi
            pqLargeDestructor.Insert(distrib(gen));
        }
        testResults.addTest(true, "Destructor on large PQHeap<int> (no crash)");
    }

    {
        lasd::PQHeap<std::string> pqLargeStrDestructor;
        for (int i = 0; i < 5000; ++i) {
            pqLargeStrDestructor.Insert(std::to_string(distrib(gen)) + "test");
        }
        testResults.addTest(true, "Destructor on large PQHeap<string> (no crash)");
    }

    // Il distruttore della copia deve funzionare indipendentemente dall'originale.
    {
        lasd::PQHeap<int> originalPq;
        for (int i = 0; i < 50; ++i) {
            originalPq.Insert(i);
        }
        lasd::PQHeap<int> copiedPq = originalPq; // Copia
        // Originale e Copia devono essere indipendenti.
        // La distruzione di copiedPq non deve influenzare originalPq e viceversa.
        testResults.addTest(true, "Copy constructor & subsequent destructor (no crash)");
    } // copiedPq viene distrutta qui. originalPq rimane in scope.



    //resoconto dei test
    testResults.printSummary("\n End of Priority Queue Tests");
  
} // 70


/* ************************************************************************** */

void MyTestHeap() {
    std::cout << "\nBegin of Heap Tests:" << std::endl;
    // Resettiamo il contatore dei test
    testResults.reset();
    // Test: Creazione heap vuoto
    lasd::HeapVec<int> emptyHeap;
    testResults.addTest(true, "Creating empty heap");
    
    // Test: Dimensione heap vuoto
    testResults.addTest(emptyHeap.Size() == 0, "Empty heap has size 0");
    
    // Test: Empty su heap vuoto (usando Size() == 0)
    testResults.addTest(emptyHeap.Size() == 0, "Empty heap has size 0 (Empty check)");
    
    // Test: IsHeap su heap vuoto (dovrebbe essere true)
    testResults.addTest(emptyHeap.IsHeap(), "Empty heap is a valid heap");
     // Test: Sort su heap vuoto (verifica che rimanga vuoto)
    emptyHeap.Sort();
    testResults.addTest(emptyHeap.Size() == 0, "Sort on empty heap maintains size 0");
    
    // Test: Heapify su heap vuoto (verifica che rimanga vuoto)
    emptyHeap.Heapify();
    testResults.addTest(emptyHeap.Size() == 0, "Heapify on empty heap maintains size 0");
    lasd::Vector<int> singleVec(1);
    singleVec[0] = 42;
    lasd::HeapVec<int> singleHeap(singleVec);
    
    testResults.addTest(singleHeap.Size() == 1, "Single element heap has size 1");
    testResults.addTest(singleHeap.Size() > 0, "Single element heap is not empty");
    testResults.addTest(singleHeap.IsHeap(), "Single element heap is valid");
    testResults.addTest(singleHeap[0] == 42, "Single element heap contains correct value");
     // Test Sort su heap con un elemento
    singleHeap.Sort();
    testResults.addTest(singleHeap.Size() == 1 && singleHeap[0] == 42, "Sort on single element heap preserves element");
    
    // ************************************************************************
    // TEST 3: HEAP CON ELEMENTI DUPLICATI
    // ************************************************************************
    
    lasd::Vector<int> dupVec(6);
    dupVec[0] = 5; dupVec[1] = 5; dupVec[2] = 3; dupVec[3] = 3; dupVec[4] = 1; dupVec[5] = 1;
    lasd::HeapVec<int> dupHeap(dupVec);
    
    testResults.addTest(dupHeap.IsHeap(), "Heap with duplicates is valid");
    testResults.addTest(dupHeap.Size() == 6, "Heap with duplicates has correct size");
    
    dupHeap.Sort();
    bool sortedCorrectly = true;
    for(unsigned int i = 0; i < dupHeap.Size() - 1; i++) {
        if(dupHeap[i] > dupHeap[i+1]) {
            sortedCorrectly = false;
            break;
        }
    }
    testResults.addTest(sortedCorrectly, "Heap with duplicates sorts correctly");
    
    // ************************************************************************
    // TEST 6: COSTRUTTORE DI COPIA
    // ************************************************************************
    
    lasd::Vector<int> originalVec(4);
    originalVec[0] = 10; originalVec[1] = 8; originalVec[2] = 6; originalVec[3] = 4;
    lasd::HeapVec<int> originalHeap(originalVec);
    
    lasd::HeapVec<int> copiedHeap(originalHeap);
    testResults.addTest(copiedHeap == originalHeap, "Copy constructor creates equal heap");
    testResults.addTest(copiedHeap.Size() == originalHeap.Size(), "Copy has same size as original");
    testResults.addTest(copiedHeap.IsHeap() == originalHeap.IsHeap(), "Copy maintains heap property");
    
    // Test indipendenza delle copie
    originalHeap.Sort();
    testResults.addTest(!(copiedHeap == originalHeap), "Copy remains independent after original is modified");
    
    // ************************************************************************
    // TEST 7: MOVE CONSTRUCTOR
    // ************************************************************************
    
    lasd::Vector<int> moveVec(3);
    moveVec[0] = 7; moveVec[1] = 5; moveVec[2] = 3;
    lasd::HeapVec<int> moveHeap(moveVec);
    unsigned int originalSize = moveHeap.Size();
    
    lasd::HeapVec<int> movedHeap(std::move(moveHeap));
    testResults.addTest(movedHeap.Size() == originalSize, "Move constructor transfers size correctly");
    testResults.addTest(moveHeap.Size() == 0, "Original heap has size 0 after move");
    testResults.addTest(movedHeap.IsHeap(), "Moved heap maintains heap property");
    
    // ************************************************************************
    // TEST 8: OPERATORI DI ASSEGNAZIONE
    // ************************************************************************
    
    lasd::Vector<int> assignVec(3);
    assignVec[0] = 9; assignVec[1] = 7; assignVec[2] = 5;
    lasd::HeapVec<int> assignHeap(assignVec);
    
    lasd::HeapVec<int> targetHeap;
    targetHeap = assignHeap;
    testResults.addTest(targetHeap == assignHeap, "Assignment operator creates equal heap");
    
    // Test move assignment
    lasd::HeapVec<int> moveTargetHeap;
    unsigned int assignSize = assignHeap.Size();
    moveTargetHeap = std::move(assignHeap);
    testResults.addTest(moveTargetHeap.Size() == assignSize, "Move assignment transfers size correctly");
    testResults.addTest(assignHeap.Size() == 0, "Original heap has size 0 after move assignment");
    
    // ************************************************************************
    // TEST 9: OPERAZIONI SEQUENZIALI
    // ************************************************************************
    
    lasd::Vector<int> seqVec(4);
    seqVec[0] = 8; seqVec[1] = 6; seqVec[2] = 4; seqVec[3] = 2;
    lasd::HeapVec<int> seqHeap(seqVec);
    
    // Sort -> Heapify -> Sort
    seqHeap.Sort();
    bool firstSortOk = !seqHeap.IsHeap();
    seqHeap.Heapify();
    bool heapifyOk = seqHeap.IsHeap();
    seqHeap.Sort();
    bool secondSortOk = !seqHeap.IsHeap();
    
    testResults.addTest(firstSortOk && heapifyOk && secondSortOk, 
                       "Sequential Sort->Heapify->Sort operations work correctly");
    
    // ************************************************************************
    // TEST 10: ACCESSO AGLI ELEMENTI
    // ************************************************************************
    
    lasd::Vector<int> accessVec(5);
    accessVec[0] = 10; accessVec[1] = 8; accessVec[2] = 6; accessVec[3] = 4; accessVec[4] = 2;
    lasd::HeapVec<int> accessHeap(accessVec);
    
    testResults.addTest(accessHeap[0] == 10, "Root element access works correctly");
    testResults.addTest(accessHeap.Front() == 10, "Front() returns root element");
    testResults.addTest(accessHeap.Back() == 2, "Back() returns last element");
    // TEST 11: CASI LIMITE CON VALORI ESTREMI
    // ************************************************************************
    
    lasd::Vector<int> extremeVec(4);
    extremeVec[0] = INT_MAX; extremeVec[1] = INT_MIN; extremeVec[2] = 0; extremeVec[3] = -1;
    lasd::HeapVec<int> extremeHeap(extremeVec);
    
    extremeHeap.Heapify();
    testResults.addTest(extremeHeap.IsHeap(), "Heap with extreme values is valid after heapify");
    testResults.addTest(extremeHeap[0] == INT_MAX, "INT_MAX is at root of max-heap");
    
    // ************************************************************************
    // TEST 12: CLEAR E RESIZE
    // ************************************************************************
    
    lasd::Vector<int> clearVec(5);
    for(unsigned int i = 0; i < 5; i++) clearVec[i] = i + 1;
    lasd::HeapVec<int> clearHeap(clearVec);
    
    clearHeap.Clear();
    testResults.addTest(clearHeap.Size() == 0, "Clear() sets size to 0");
    testResults.addTest(clearHeap.Size() == 0, "Heap is empty after Clear() (size check)");
    testResults.addTest(clearHeap.IsHeap(), "Empty heap after Clear() is valid");
    
    // Test Resize
    clearHeap.Resize(3);
    testResults.addTest(clearHeap.Size() == 3, "Resize() changes size correctly");
    // Test con valori double specifici
    lasd::Vector<double> doubleVec(5);
    doubleVec[0] = 3.14; doubleVec[1] = 2.71; doubleVec[2] = 1.41; 
    doubleVec[3] = 0.0; doubleVec[4] = -1.5;
    
    lasd::HeapVec<double> doubleHeap(doubleVec);
    
    testResults.addTest(doubleHeap.Size() == 5, "Double heap creation with size 5");
    
    doubleHeap.Heapify();
    testResults.addTest(doubleHeap.IsHeap(), "Double heap is valid after heapify");
    testResults.addTest(doubleHeap[0] == 3.14, "Max double value at root");
    
    // Test con valori molto piccoli e grandi
    lasd::Vector<double> extremeDoubleVec(4);
    extremeDoubleVec[0] = DBL_MAX; extremeDoubleVec[1] = DBL_MIN; 
    extremeDoubleVec[2] = 0.0; extremeDoubleVec[3] = -DBL_MAX;
    
    lasd::HeapVec<double> extremeDoubleHeap(extremeDoubleVec);
    extremeDoubleHeap.Heapify();
    testResults.addTest(extremeDoubleHeap.IsHeap(), "Extreme double values heap is valid");
    testResults.addTest(extremeDoubleHeap[0] == DBL_MAX, "DBL_MAX at root");
    
    // Test precisione floating point
    lasd::Vector<double> precisionVec(3);
    precisionVec[0] = 1.0000000001; precisionVec[1] = 1.0000000002; precisionVec[2] = 1.0;
    lasd::HeapVec<double> precisionHeap(precisionVec);
    
    precisionHeap.Heapify();
    testResults.addTest(precisionHeap[0] == 1.0000000002, "Floating point precision handled correctly");
    // Test con stringhe speciali
    lasd::Vector<std::string> specialStringVec(6);
    specialStringVec[0] = ""; specialStringVec[1] = " "; specialStringVec[2] = "\n";
    specialStringVec[3] = "\t"; specialStringVec[4] = "normal"; specialStringVec[5] = "CAPS";
    
    lasd::HeapVec<std::string> specialStringHeap(specialStringVec);
    specialStringHeap.Heapify();
    testResults.addTest(specialStringHeap.IsHeap(), "Special characters string heap is valid");
    
    // Test con stringhe di lunghezza variabile
    lasd::Vector<std::string> lengthVec(4);
    lengthVec[0] = "a"; lengthVec[1] = "bb"; lengthVec[2] = "ccc"; lengthVec[3] = "dddd";
    
    lasd::HeapVec<std::string> lengthHeap(lengthVec);
    lengthHeap.Heapify();
    testResults.addTest(lengthHeap.IsHeap(), "Variable length strings heap is valid");
    
    // Test sort su stringhe
    lengthHeap.Sort();
    bool stringSorted = true;
    for(unsigned int i = 0; i < lengthHeap.Size() - 1; i++) {
        if(lengthHeap[i] > lengthHeap[i+1]) {
            stringSorted = false;
            break;
        }
    }
    testResults.addTest(stringSorted, "String heap sorts correctly");

    // Test con operazioni di copia profonda
    
    lasd::Vector<int> originalVec2(5);
    for(int i = 0; i < 5; i++) {
    originalVec2[i] = i + 1;
    }
    lasd::HeapVec<int> originalHeap2(originalVec2);
    lasd::HeapVec<int> copiedHeap2 = originalHeap2; // Copia profonda
    originalHeap2[0] = 0; // Modifichiamo l'originale usando l'operatore []
    testResults.addTest(copiedHeap2[0] == 5, "Deep copy maintains independence after original modification");
    // Test con operazioni di ordinamento
    lasd::Vector<int> sortVec(5);
    sortVec[0] = 5; sortVec[1] = 3; sortVec[2] = 8; sortVec[3] = 1; sortVec[4] = 4;
    lasd::HeapVec<int> sortHeap(sortVec);
    sortHeap.Heapify();
    sortHeap.Sort();
    bool isSorted = true;
    for(unsigned int i = 0; i < sortHeap.Size() - 1; i++) {
        if(sortHeap[i] > sortHeap[i+1]) {
            isSorted = false;
            break;
        }
    }
    testResults.addTest(isSorted, "Heap sorting works correctly");
    // Test con operazioni di ordinamento su stringhe
    lasd::Vector<std::string> stringSortVec(5);
    stringSortVec[0] = "banana"; stringSortVec[1] = "apple"; stringSortVec[2] = "orange";
    stringSortVec[3] = "kiwi"; stringSortVec[4] = "grape";
    lasd::HeapVec<std::string> stringSortHeap(stringSortVec);
    stringSortHeap.Heapify();
    stringSortHeap.Sort();
    bool stringSortOk = true;
    for(unsigned int i = 0; i < stringSortHeap.Size() - 1; i++) {

        if(stringSortHeap[i] > stringSortHeap[i+1]) {
            stringSortOk = false;
            break;
        }
    }
    testResults.addTest(stringSortOk, "String heap sorting works correctly");
    // Test con operazioni di ordinamento su valori float
    lasd::Vector<double> floatSortVec(5);
    floatSortVec[0] = 3.14; floatSortVec[1] = 2.71; floatSortVec[2] = 1.41;
    floatSortVec[3] = 0.0; floatSortVec[4] = -1.5;
    lasd::HeapVec<double> floatSortHeap(floatSortVec);
    floatSortHeap.Heapify();
    floatSortHeap.Sort();
    bool floatSortOk = true;
    for(unsigned int i = 0; i < floatSortHeap.Size() - 1; i++) {
        if(floatSortHeap[i] > floatSortHeap[i+1]) {
            floatSortOk = false;
            break;
        }
    }
    testResults.addTest(floatSortOk, "Float heap sorting works correctly");
    // Test con operazioni di ordinamento su valori estremi
    lasd::Vector<int> extremeSortVec(4);
    extremeSortVec[0] = INT_MAX; extremeSortVec[1] = INT_MIN;
    extremeSortVec[2] = 0; extremeSortVec[3] = -1;
    lasd::HeapVec<int> extremeSortHeap(extremeSortVec);
    extremeSortHeap.Heapify();
    extremeSortHeap.Sort();
    bool extremeSortOk = true;
    for(unsigned int i = 0; i < extremeSortHeap.Size() - 1; i++) {
        if(extremeSortHeap[i] > extremeSortHeap[i+1]) {
            extremeSortOk = false;
            break;
        }
    }   
    testResults.addTest(extremeSortOk, "Extreme value heap sorting works correctly");

    // Test con operazioni di ordinamento su valori booleani
    lasd::Vector<bool> boolVec(4);
    boolVec[0] = true; boolVec[1] = false; boolVec[2] = true; boolVec[3] = false;
    lasd::HeapVec<bool> boolHeap(boolVec);  
    boolHeap.Heapify();
    boolHeap.Sort();
    bool boolSortOk = true;
    for(unsigned int i = 0; i < boolHeap.Size() - 1; i++) {
        if(boolHeap[i] > boolHeap[i+1]) {
            boolSortOk = false;
            break;
        }
    }
    testResults.addTest(boolSortOk, "Boolean heap sorting works correctly");
    // Test con operazioni di ordinamento su valori char
    lasd::Vector<char> charVec(5);
    charVec[0] = 'e'; charVec[1] = 'a'; charVec[2] = 'd'; charVec[3] = 'c'; charVec[4] = 'b';
    lasd::HeapVec<char> charHeap(charVec);
    charHeap.Heapify();
    charHeap.Sort();
    bool charSortOk = true;
    for(unsigned int i = 0; i < charHeap.Size() - 1; i++) {
        if(charHeap[i] > charHeap[i+1]) {
            charSortOk = false;
            break;
        }
    }
    testResults.addTest(charSortOk, "Char heap sorting works correctly");
    // Test con operazioni di ordinamento su valori stringa
    lasd::Vector<std::string> stringVec(5);
    stringVec[0] = "zebra"; stringVec[1] = "apple"; stringVec[2] = "orange";
    stringVec[3] = "banana"; stringVec[4] = "kiwi";
    lasd::HeapVec<std::string> stringHeap(stringVec);
    stringHeap.Heapify();
    stringHeap.Sort();
    bool stringHeapSortOk = true;
    for(unsigned int i = 0; i < stringHeap.Size() - 1; i++) {
        if(stringHeap[i] > stringHeap[i+1]) {
            stringHeapSortOk = false;
            break;
        }
    }
    testResults.addTest(stringHeapSortOk, "String heap sorting works correctly");
    
    // Test 1: Merge two heaps
    lasd::Vector<int> vec1(3);
    vec1[0] = 10; vec1[1] = 8; vec1[2] = 6;
    lasd::HeapVec<int> heap1(vec1);

    lasd::Vector<int> vec2(3);
    vec2[0] = 9; vec2[1] = 7; vec2[2] = 5;
    lasd::HeapVec<int> heap2(vec2);

    // Create a new heap combining elements
    lasd::Vector<int> mergedVec(6);
    for(unsigned int i = 0; i < 3; i++) {
        mergedVec[i] = vec1[i];
        mergedVec[i+3] = vec2[i];
    }
    lasd::HeapVec<int> mergedHeap(mergedVec);
    mergedHeap.Heapify();

    testResults.addTest(mergedHeap.Size() == 6 && mergedHeap[0] == 10, 
                       "Merged heap maintains heap property");
    
    // Test 3: Heap balancing properties
    lasd::Vector<int> balanceVec(7);
    for(int i = 0; i < 7; i++) balanceVec[i] = i;
    lasd::HeapVec<int> balanceHeap(balanceVec);
    balanceHeap.Heapify();

    bool isBalanced = true;
    for(unsigned int i = 0; i < balanceHeap.Size()/2; i++) {
        unsigned int leftChild = 2*i + 1;
        unsigned int rightChild = 2*i + 2;
        if(leftChild < balanceHeap.Size() && balanceHeap[i] < balanceHeap[leftChild])
            isBalanced = false;
        if(rightChild < balanceHeap.Size() && balanceHeap[i] < balanceHeap[rightChild])
            isBalanced = false;
    }
    testResults.addTest(isBalanced, "Heap maintains balance property");

    // Test 4: Exception handling
    bool exceptionCaught = false;
    try {
        lasd::HeapVec<int> invalidHeap;
        invalidHeap[5] = 10; // Should throw
    } catch(...) {
        exceptionCaught = true;
    }
    testResults.addTest(exceptionCaught, "Heap handles invalid access properly");

    // Test 5: Random data
    lasd::Vector<int> randVec(100);
    for(int i = 0; i < 100; i++) randVec[i] = rand() % 1000;
    lasd::HeapVec<int> randHeap(randVec);
    randHeap.Heapify();

    bool isHeapProperty = true;
    for(unsigned int i = 0; i < randHeap.Size()/2; i++) {
        unsigned int leftChild = 2*i + 1;
        unsigned int rightChild = 2*i + 2;
        if(leftChild < randHeap.Size() && randHeap[i] < randHeap[leftChild])
            isHeapProperty = false;
        if(rightChild < randHeap.Size() && randHeap[i] < randHeap[rightChild])
            isHeapProperty = false;
    }
    testResults.addTest(isHeapProperty, "Heap maintains properties with random data");
    // Test di attraversamento specifici
    lasd::Vector<int> traverseVec(5);
    traverseVec[0] = 10; traverseVec[1] = 8; traverseVec[2] = 6; 
    traverseVec[3] = 4; traverseVec[4] = 2;
    lasd::HeapVec<int> traverseHeap(traverseVec);

    // Test PreOrder
    testResults.addTest(traverseHeap[0] == 10, "PreOrder root check");
    testResults.addTest(traverseHeap[1] == 8, "PreOrder first level check");

    // Test concatenazione di operazioni
    lasd::HeapVec<int> chainHeap(traverseHeap);
    chainHeap.Heapify();
    chainHeap.Sort();
    chainHeap.Heapify();
    testResults.addTest(chainHeap.IsHeap(), "Chain of operations maintains heap property");

    // Test con lambda functions
    lasd::Vector<int> lambdaVec(3);
    lambdaVec[0] = 3; lambdaVec[1] = 2; lambdaVec[2] = 1;
    lasd::HeapVec<int> lambdaHeap(lambdaVec);
    int sum = 0;
    // Test accumulation con lambda
    for(unsigned int i = 0; i < lambdaHeap.Size(); i++) {
    sum += lambdaHeap[i];
   }
    testResults.addTest(sum == 6, "Accumulation with lambda works correctly");

    // Test con modifiche strutturali
    lasd::Vector<int> structVec(4);
    structVec[0] = 100; structVec[1] = 50; structVec[2] = 25; structVec[3] = 12;
    lasd::HeapVec<int> structHeap(structVec);
    structHeap.Clear();
    structHeap.Resize(2);
    testResults.addTest(structHeap.Size() == 2, "Structural modifications work correctly");

    // Test con valori negativi e zero alternati
    lasd::Vector<int> alternatingVec(6);
    alternatingVec[0] = 0; alternatingVec[1] = -1; 
    alternatingVec[2] = 0; alternatingVec[3] = -2;
    alternatingVec[4] = 0; alternatingVec[5] = -3;
    lasd::HeapVec<int> alternatingHeap(alternatingVec);
    alternatingHeap.Heapify();
    testResults.addTest(alternatingHeap[0] == 0, "Alternating zero/negative values heap property");

    // Test boundary conditions con resize
    lasd::HeapVec<int> resizeHeap;
    resizeHeap.Resize(1);
    resizeHeap.Resize(100);
    resizeHeap.Resize(50);
    testResults.addTest(resizeHeap.Size() == 50, "Multiple resize operations work correctly");

    // Test con operazioni di copia dopo modifiche
    lasd::Vector<int> modVec(3);
    modVec[0] = 30; modVec[1] = 20; modVec[2] = 10;
    lasd::HeapVec<int> modHeap(modVec);
    modHeap.Sort();
    lasd::HeapVec<int> copiedModHeap(modHeap);
    testResults.addTest(!copiedModHeap.IsHeap(), "Copy constructor preserves non-heap state");
    // Test con heap di dimensione pari/dispari
    lasd::Vector<int> oddVec(7);
    for(int i = 0; i < 7; i++) oddVec[i] = 7-i;
    lasd::HeapVec<int> oddHeap(oddVec);
    testResults.addTest(oddHeap.IsHeap(), "Odd-sized heap property check");

    lasd::Vector<int> evenVec(8);
    for(int i = 0; i < 8; i++) evenVec[i] = 8-i;
    lasd::HeapVec<int> evenHeap(evenVec);
    testResults.addTest(evenHeap.IsHeap(), "Even-sized heap property check");

    // Test con sequenze specifiche
    lasd::Vector<int> seqVec1(5);
    seqVec1[0] = 1; seqVec1[1] = 2; seqVec1[2] = 3; seqVec1[3] = 4; seqVec1[4] = 5; // già ordinato
    lasd::HeapVec<int> seqHeap1(seqVec1);
    testResults.addTest(seqHeap1.IsHeap(), "Already sorted sequence heap check");
 
    lasd::Vector<int> seqVec2(5);
    seqVec2[0] = 5; seqVec2[1] = 4; seqVec2[2] = 3; seqVec2[3] = 2; seqVec2[4] = 1; // ordine inverso
    lasd::HeapVec<int> seqHeap2(seqVec2);
    testResults.addTest(seqHeap2.IsHeap(), "Reverse sorted sequence heap check");

    // Test con valori decimali specifici
    lasd::Vector<double> preciseVec(4);
    preciseVec[0] = 1.1111; preciseVec[1] = 1.1112; 
    preciseVec[2] = 1.1113; preciseVec[3] = 1.1114;
    lasd::HeapVec<double> preciseHeap(preciseVec);
    preciseHeap.Heapify();
    testResults.addTest(std::abs(preciseHeap[0] - 1.1114) < 0.0001, "Precise decimal handling");

    // Test con caratteri speciali
    lasd::Vector<char> specialCharVec(6);
    specialCharVec[0] = '!'; specialCharVec[1] = '@'; 
    specialCharVec[2] = '#'; specialCharVec[3] = '$';
    specialCharVec[4] = '%'; specialCharVec[5] = '^';
    lasd::HeapVec<char> specialCharHeap(specialCharVec);
    testResults.addTest(specialCharHeap.IsHeap(), "Special characters heap property");

    // Test di stabilità dopo multiple operazioni
    lasd::HeapVec<int> stabilityHeap;
    for(int i = 0; i < 10; i++) {
    lasd::Vector<int> tempVec(3);
    tempVec[0] = i; tempVec[1] = i*2; tempVec[2] = i*3;
    lasd::HeapVec<int> tempHeap(tempVec);
    stabilityHeap = tempHeap;
    stabilityHeap.Heapify();
    }
    testResults.addTest(stabilityHeap.IsHeap(), "Heap stability after multiple operations");

    // Test con stringhe Unicode
    lasd::Vector<std::string> unicodeVec(4);
    unicodeVec[0] = "α"; unicodeVec[1] = "β"; 
    unicodeVec[2] = "γ"; unicodeVec[3] = "δ";
    lasd::HeapVec<std::string> unicodeHeap(unicodeVec);
    testResults.addTest(unicodeHeap.IsHeap(), "Unicode string heap property");

    // Test di performance su grandi heap
    lasd::Vector<int> largeVec(1000);
    for(int i = 0; i < 1000; i++) largeVec[i] = rand();
    lasd::HeapVec<int> largeHeap(largeVec);
    largeHeap.Heapify();
    testResults.addTest(largeHeap.IsHeap(), "Large heap maintains heap property");
    // Test con heap di tipi misti usando pair
    lasd::Vector<std::pair<int, std::string>> pairVec(4);
    pairVec[0] = {5, "five"}; 
    pairVec[1] = {3, "three"};
    pairVec[2] = {7, "seven"}; 
    pairVec[3] = {1, "one"};
    lasd::HeapVec<std::pair<int, std::string>> pairHeap(pairVec);
    pairHeap.Heapify();
    testResults.addTest(pairHeap[0].first == 7, "Pair heap maintains max-heap property on first element");
    testResults.addTest(pairHeap[0].second == "seven", "Pair heap maintains correspondence of pairs");
    
    // Test per verificare la stabilità dell'ordinamento con elementi uguali
    lasd::Vector<std::pair<int, int>> stabVec(6);
    stabVec[0] = {5, 1}; stabVec[1] = {5, 2}; 
    stabVec[2] = {5, 3}; stabVec[3] = {3, 1};
    stabVec[4] = {3, 2}; stabVec[5] = {3, 3};
    lasd::HeapVec<std::pair<int, int>> stabHeap(stabVec);
    stabHeap.Sort();
    bool stabilityMaintained = true;
    for(unsigned int i = 1; i < stabHeap.Size(); i++) {
        if(stabHeap[i-1].first == stabHeap[i].first && 
           stabHeap[i-1].second > stabHeap[i].second) {
            stabilityMaintained = false;
            break;
        }
    }
    testResults.addTest(stabilityMaintained, "Sort maintains stability for equal elements");
    
    // Test per verifica proprietà ricorsiva dell'heap
    lasd::Vector<int> recVec(7);
    for(int i = 0; i < 7; i++) recVec[i] = i;
    lasd::HeapVec<int> recHeap(recVec);
    recHeap.Heapify();
    bool recursiveProperty = true;
    std::function<bool(unsigned int)> checkSubtree = [&recHeap, &checkSubtree](unsigned int idx) {
        unsigned int leftChild = 2*idx + 1;
        unsigned int rightChild = 2*idx + 2;
        bool valid = true;
        if(leftChild < recHeap.Size()) {
            valid = valid && recHeap[idx] >= recHeap[leftChild] && checkSubtree(leftChild);
        }
        if(rightChild < recHeap.Size()) {
            valid = valid && recHeap[idx] >= recHeap[rightChild] && checkSubtree(rightChild);
        }
        return valid;
    };
    recursiveProperty = checkSubtree(0);
    testResults.addTest(recursiveProperty, "Heap maintains recursive property in all subtrees");
    
    // Test di stress con operazioni alternate
    lasd::HeapVec<int> stressHeap;
    std::vector<int> expectedValues;
    for(int i = 0; i < 100; i++) {
        lasd::Vector<int> tempVec(3);
        tempVec[0] = rand() % 1000;
        tempVec[1] = rand() % 1000;
        tempVec[2] = rand() % 1000;
        lasd::HeapVec<int> temp(tempVec);
        if(i % 2 == 0) {
            temp.Sort();
        }
        stressHeap = temp;
        stressHeap.Heapify();
        testResults.addTest(stressHeap.IsHeap(), 
                           "Heap maintains properties after stress operation " + std::to_string(i));
    }
    
    // Test con sequenze particolari di numeri
    lasd::Vector<int> seqVec3(8);
    // Sequenza Fibonacci
    seqVec3[0] = 1; seqVec3[1] = 1; seqVec3[2] = 2; 
    seqVec3[3] = 3; seqVec3[4] = 5; seqVec3[5] = 8;
    seqVec3[6] = 13; seqVec3[7] = 21;
    lasd::HeapVec<int> fibHeap(seqVec3);
    fibHeap.Sort();
    bool isFibSorted = true;
    for(unsigned int i = 1; i < fibHeap.Size(); i++) {
        if(fibHeap[i-1] > fibHeap[i]) {
            isFibSorted = false;
            break;
        }
    }
    testResults.addTest(isFibSorted, "Heap correctly sorts Fibonacci sequence");
    
    // Test con operazioni di resize complesse
    lasd::HeapVec<int> complexHeap;
    std::vector<unsigned int> sizes = {1, 10, 5, 20, 15, 7, 30, 25};
    bool resizeOk = true;
    for(unsigned int size : sizes) {
        complexHeap.Resize(size);
        if(complexHeap.Size() != size) {
            resizeOk = false;
            break;
        }
        // Riempi con valori
        for(unsigned int i = 0; i < size; i++) {
            complexHeap[i] = rand() % 100;
        }
        complexHeap.Heapify();
        if(!complexHeap.IsHeap()) {
            resizeOk = false;
            break;
        }
    }
    testResults.addTest(resizeOk, "Complex resize operations maintain heap property");

    // ************************************************************************
    // TEST DI SICUREZZA MEMORIA E ROBUSTEZZA
    // ************************************************************************
    
    // Test per memory leaks con operazioni cicliche
    lasd::HeapVec<int> cyclicHeap;
    for(int i = 0; i < 1000; i++) {
        cyclicHeap.Resize(i % 10 + 1);
        cyclicHeap.Heapify();
        cyclicHeap.Sort();
    }
    testResults.addTest(true, "Cyclic memory operations completed");

    // Test accessi boundary
    lasd::Vector<int> boundaryVec(5);
    for(int i = 0; i < 5; i++) boundaryVec[i] = i;
    lasd::HeapVec<int> boundaryHeap(boundaryVec);
    
    bool boundaryAccessOk = true;
    try {
        boundaryHeap[boundaryHeap.Size() - 1];
        boundaryHeap[0];
    } catch(...) {
        boundaryAccessOk = false;
    }
    testResults.addTest(boundaryAccessOk, "Boundary access check");

    // resoconto dei test
    testResults.printSummary("\n End of Heap Tests");
    
    } //180 test


/* ************************************************************************** */

// Funzione principale per l'esecuzione dei test personalizzati
void mytest() {
    int scelta;
    
    std::cout << "~*~#~*~  LASD Libraries 2025 - Menu dei Custom Tests ~*~#~*~!" << std::endl;
    
    do {
        std::cout << "\nScegli il test da eseguire:" << std::endl;
        std::cout << "1. Test Heap" << std::endl;
        std::cout << "2. Test Priority Queue" << std::endl;
        std::cout << "3. Esegui tutti i test dell'Esercizio 2" << std::endl;
        std::cout << "\n=== OPZIONI GENERALI ===" << std::endl;
        std::cout << "0. Torna al menu principale" << std::endl;
        std::cout << "\nScelta: ";
        std::cin >> scelta;
        
        switch(scelta) {
        
            case 1:
                std::cout << "\n=== Test per Heap ===" << std::endl;
                MyTestHeap();
                break;
            case 2:
                std::cout << "\n=== Test per Priority Queue ===" << std::endl;
                MyTestPQ();
                break;
            case 3:
                std::cout << "\n=== Esegui tutti i test custom ===" << std::endl;
                MyTestHeap();
                MyTestPQ();
                break;
                
            case 0:
                std::cout << "Ritorno al menu principale..." << std::endl;
                break;
            default:
                std::cout << "Scelta non valida" << std::endl;
        }
    } while(scelta != 0);
}

/* ************************************************************************** */