/*
Meno a priezvisko:

POKYNY:
(1)  Implementujte funkcie tak, aby splnali popis pri ich deklaraciach.
(2)  Cela implementacia musi byt v tomto jednom subore.
(3)  Odovzdajte len tento zdrojovy subor (s vypracovanymi rieseniami).
(4)  Program musi byt kompilovatelny.
(5)  Globalne a staticke premenne su zakazane.
(6)  V ziadnom pripade nemente deklaracie funkcii, ktore mate za ulohu naprogramovat
     (nemente nazvy, navratove hodnoty, ani typ a pocet parametrov v zadanych funkciach).
     Nemente implementacie zadanych datovych typov, ani implementacie hotovych pomocnych funkcii
     (ak nie je v zadani ulohy uvedene inak).
(7)  V pripade potreby mozete kod doplnit o dalsie pomocne funkcie alebo datove typy.
(8)  V prvych osmich prikladoch mozete pouzit iterativnu alebo rekurzivnu implementaciu. <- SPECIALNE INSTRUKCIE PRE TOTO ZADANIE
     V pripade implementacie rekurziou, moze byt hlavna cast implemetovana v pridanej rekurzivnej funkcii. <- SPECIALNE INSTRUKCIE PRE TOTO ZADANIE
(9)  Vase riesenie otestujte (vo funkcii 'main' a pomocou doplnenych pomocnych funkcii alebo datovych typov).
     Testovaci kod ale nebude hodnoteny.
(10) Funkcia 'main' musi byt v zdrojovom kode posledna.
*/


#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <exception>
#include <set>

using namespace std;

//-------------------------------------------------------------------------------------------------
// DATOVE TYPY
//-------------------------------------------------------------------------------------------------

// Uzol binarneho vyhladavacieho stromu
struct Node {
    int value;     // hodnota uzla
    Node *smaller; // uzol 'smaller' a jeho nasledovnici maju hodnotu mensiu ako 'value'
    Node *greater; // uzol 'greater' a jeho nasledovnici maju hodnotu vacsiu ako 'value

    explicit Node(int value = 0, Node *smaller = nullptr, Node *greater = nullptr)
    : value(value)
    , smaller(smaller)
    , greater(greater)
    {
    }
};

// Binarny vyhladavaci strom
struct BinarySearchTree {
    Node *root; // koren stromu

    explicit BinarySearchTree(Node *root = nullptr)
    : root(root)
    {
    }
};

// Vynimka oznacujuca, ze uzol so zadanou hodnotou v strome neexistuje
class ValueNotExistsException : public std::exception {
};

//-------------------------------------------------------------------------------------------------
// 1. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati najmensiu hodnotu v strome.
    V pripade neexistencie tejto hodnoty vyhodi vynimku.

    Riesenie (tejto, aj dalsich uloh) musi vyuzivat vlastnosti binarneho vyhladavacieho stromu.
    Napriklad, pri hladani minima treba prejst len cez potrebne uzly. Netreba prehladavat vsetky uzly (okrem specialnych pripadov).

    VSTUPNY PARAMETER:
        [in] tree - strom, v ktorom funkcia hlada minimum

    NAVRATOVA HODNOTA:
        najmensia hodnota v strome

    VYNIMKA:
        ValueNotExistsException - ak je strom prazdny
*/

int min(const BinarySearchTree *tree) {
    if (tree == nullptr || tree->root == nullptr) {
        throw ValueNotExistsException();
    }
    int minimum;
    Node* pod=tree->root;
    while(1){
        if(pod->smaller!= nullptr){
            pod=pod->smaller;
        }
        else{
            return pod->value;
        }
    }
}

//-------------------------------------------------------------------------------------------------
// 2. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati hlbku uzla s hodnotou 'value' v strome 'tree'.
    Hlbka korena je 0.
    Ak hladany uzol v strome nie je, tak funkcia vyhodi vynimku.

    VSTUPNE PARAMETRE:
        [in] tree - strom, v ktorom funkcia hlada uzol
        [in] value - hodnota hladaneho uzla

    NAVRATOVA HODNOTA:
        Hlbka uzla s hodnotou 'value'.

    VYNIMKA:
        ValueNotExistsException - ak sa uzol s hodnotou 'value' v strome nenachdza
*/

unsigned depth(const BinarySearchTree *tree, int value) {
    if (tree == nullptr || tree->root == nullptr) {
        throw ValueNotExistsException();
    }
    int hlbka=0;
    Node* pod=tree->root;
    while(1){
        if(pod->value==value){
            return hlbka;
        }
        if(pod->value>value){
            if(pod->smaller== nullptr){
                throw ValueNotExistsException();
            }
            else{
                pod=pod->smaller;
            }
        }
        else{
            if(pod->greater== nullptr){
                throw ValueNotExistsException();
            }
            else{
                pod=pod->greater;
            }
        }
        hlbka++;
    }
    return ~0; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// 3. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati zoznam hodnot uzlov, ktore musi prejst pri hladani uzla s hodnotou 'value'.
    Prva hodnota vystupneho zoznamu je hodnota korena, druha hodnota zoznamu je lavy alebo pravy nasledovnik korena, atd.
    Poslednou hodnotou vo vystupnom zozname je hodnota uzla, na ktorom sa hladanie zastavilo.
    Ak 'tree' obsahuje uzol s hodnotou 'value', tak poslednou hodnotou vystupeho zoznamu je 'value'.

    VSTUPNE PARAMETRE:
        [in] tree - strom, v ktorom funkcia hlada uzol s hodnotou 'value'
        [in] value - hodnota hladaneho uzla

    NAVRATOVA HODNOTA:
        Zoznam hodnot uzlov, ktorych hodnoty musela funkcia pri hladani porovnavat.
        Poradie hodnot vo vystupnom zozname musi zodpovedat poradiu prechadzania uzlov stromu.

    PRIKLADY:
        V prikladoch predpokladajme strom:
                  40
                 /  \
               20    50
              /  \    \
            10   30    60

        1. priklad
            value: 30 -> vystup: (40, 20, 30)
        2. priklad
            value: 20 -> vystup: (40, 20)
        3. priklad
            value: 45 -> vystup: (40, 50)
*/

list<int> path(const BinarySearchTree *tree, int value) noexcept {
    list<int> zozn;
    if(tree== nullptr || tree->root== nullptr){
        return zozn;
    }
    Node* pod=tree->root;
    while(1){
        zozn.push_back(pod->value);
        if(pod->value==value){
            return zozn;
        }
        if(pod->value>value){
            if(pod->smaller== nullptr){
                return zozn;
            }
            else{
                pod=pod->smaller;
            }
        }
        else{
            if(pod->greater== nullptr){
                return zozn;
            }
            else{
                pod=pod->greater;
            }
        }
    }// tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// 4. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati pocet uzlov stromu.

    VSTUPNY PARAMETER:
        [in] tree - strom, ktoreho pocet uzlov funkcia zistuje

    NAVRATOVA HODNOTA:
        pocet uzlov stromu
*/

size_t spocitaj(const Node *heap){
    if(heap== nullptr){
        return 0;
    }
    size_t pocet=1;
    pocet+=spocitaj(heap->smaller);
    pocet+=spocitaj(heap->greater);
    return pocet;
}

size_t count(const BinarySearchTree *tree) noexcept {
    size_t pocet=spocitaj(tree->root);
    return pocet; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// 5. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati zoznam hodnot vsetkych uzlov v strome 'tree'.
    Zoznam musi byt usporiadany od najmensieho prvku po najvacsi.

    Usporiadanie dosiahnite vhodnou postupnostou prechadzania uzlov stromu!

    VSTUPNY PARAMETER:
        [in] tree - strom, ktoreho hodnoty funkcia vrati

    NAVRATOVA HODNOTA:
        hodnoty uzlov, v poradi od najmensej po najvacsiu
*/

list<int> spoj(const Node *node){
    list<int> zozn,zozn1,zozn2;
    zozn1.push_back(node->value);
    if(node->smaller!= nullptr){
        zozn=spoj(node->smaller);
    }
    if(node->greater!= nullptr){
        zozn2=spoj(node->greater);
    }
    zozn.splice(zozn.end(),zozn1);
    zozn.splice(zozn.end(),zozn2);
    return zozn;
}

list<int> all(const BinarySearchTree *tree) noexcept {
    if(tree== nullptr || tree->root== nullptr){
        list<int> zozn;
        return zozn;
    }
    return spoj(tree->root); // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// 6. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati pocet uzlov stromu 'tree', ktorych hodnota je vacsia ako 'value'.

    VSTUPNE PARAMETRE:
        [in] tree - strom, v ktorom funkcia pocita pocet uzlov splnajich podmienku
        [in] value - hodnota, podla ktorej sa vyberaju uzly

    NAVRATOVA HODNOTA:
        pocet uzlov s hodnotou vacsou ako 'value'
*/

size_t countGreaterr(const Node *tree, int value) noexcept {
    size_t pocet=0;
    if(tree== nullptr){
        return 0;
    }
    if(tree->value<=value){
        pocet+=countGreaterr(tree->greater,value);
    }
    else{
        pocet+=1;
        pocet+= spocitaj(tree->greater);
        pocet+= countGreaterr(tree->smaller,value);
    }
    return pocet;
}

size_t countGreater(const BinarySearchTree *tree, int value) noexcept {
    Node* pod=tree->root;
    return countGreaterr(pod,value);; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// 7. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia odstrani vsetky uzly stromu a dealokuje ich.

    Na dealokaciu pouzite operator 'delete'!

    VSTUPNY PARAMETER:
        [in, out] tree - strom, ktoreho uzly funkcia odstrani

    VYSTUPNE PODMIENKY:
        vsetky uzly su dealokovane
        'tree->root' je nulovy smernik
*/

void cisti_to(Node* node){
    if(node== nullptr){
        return;
    }
    cisti_to(node->smaller);
    cisti_to(node->greater);
    delete node;
}

void clear(BinarySearchTree *tree) noexcept {
    cisti_to(tree->root);
    tree->root= nullptr;
}

//-------------------------------------------------------------------------------------------------
// 8. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia hlada hodnotu 'value' vo vektore 'data'.
    Vrati pocet prvkov v 'data', ktore pri hladni porovnala s 'value'.
    Vektor 'data' obsahuje usporiadane hodnoty.
    Casova narocnost algoritmu je O(log(n)), kde n je pocet prvkov vektora.

    PARAMETRE:
        [in] data - hodnoty usporiadane od najmensieho prvku po najvacsi
        [in] value - hodnota hladana v 'data'

    NAVRATOVA HODNOTA:
        Pocet prvkov 'data', ktore funkcia pri hladani porovnala s 'value'.
        (bez ohladu na to, ci 'data' obsahuje hodnotu 'value').

    VSTUPNA PODMIENKA:
        Hodnoty v 'data' su usporiadane od najmensieho prvku po najvacsi.

    PRIKLADY:
        data = (100, 102, 104, 106, 108, 110, 112), value = 106 -> vystup: 1
        data = (100, 102, 104, 106, 108, 110, 112), value = 110 -> vystup: 2
        data = (100, 102, 104, 106, 108, 110, 112), value = 108 -> vystup: 3
        data = (100, 102, 104, 106, 108, 110), value = 104 -> vystup: 1 alebo 3
        data = (100, 102, 104, 106, 108, 110), value = 107 -> vystup: 3
        data = (100), value = 100 -> vystup: 1
        data = (100), value = 200 -> vystup: 1
        data = (), value = 100 -> vystup: 0
*/
unsigned containss(const vector<int> & data, int value,size_t zaciatok,size_t koniec) noexcept {
    if (zaciatok >= koniec) { // Ak je rozsah prázdny, vrátime počet (žiadny nález)
        return 0; // Počet porovnaní aj pri zlyhaní
    }

    size_t middle = zaciatok + (koniec - zaciatok) / 2; // Výpočet stredu
    unsigned pocet = 1; // Jedno porovnanie sa vždy vykoná

    if (data[middle] == value) { // Hodnota nájdená
        return pocet;
    } else if (value > data[middle]) { // Vyhľadávame v pravej polovici
        return pocet + containss(data, value, middle + 1, koniec);
    } else { // Vyhľadávame v ľavej polovici
        return pocet + containss(data, value, zaciatok, middle);
    }
}

unsigned contains(const vector<int> & data, int value) noexcept {
    size_t zaciatok=0,end=data.size();
    if (data.empty()) {
        return 0;
    }
    return containss(data,value,zaciatok,end);;
}

//-------------------------------------------------------------------------------------------------
// 9. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori a vrati histogram slov v 'data' (zisti, kolko krat sa ktore slovo nachadza v 'data').

    PARAMETER:
        [in] data - vektor slov

    NAVRATOVA HODNOTA:
        histogram slov (pre kazde slovo z 'data' obsahuje pocet jeho vyskytov)

    VSTUPNE PODMIENKY:
        'data' moze obsahovat lubobolny pocet slov
        'data' moze obsahovat opakujuce sa slova
        slova mozu byt prazdne retazce

    VYSTUPNE PODMIENKY:
        Histogram obsahuje iba slova, ktore sa v 'data' nachadzaju

    PRIKLADY:
        vstup: data = ("pocitac", "lietadlo", luk", "pocitac", "pocitac", "okno", "luk")
        vystup: {"pocitac" -> 3, "lietadlo" -> 1, "luk" -> 2, "okno" -> 1}

        vstup: data = ("pocitac", "")
        vystup: {"pocitac" -> 1, "" -> 1}

        vstup: data = ()
        vystup: {}
*/

map<string, size_t> histogram(const vector<string> & data) noexcept {
        map<string, size_t> result;
        for (const auto &word: data) {
            ++result[word];
        }
        return result;
}

//-------------------------------------------------------------------------------------------------
// 10. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori a vrati index slov v 'data' (pre kazde slovo mnozinu indexov jeho vyskytu).

    PARAMETER:
        [in] data - vektor slov

    NAVRATOVA HODNOTA:
        index slov (pre kazde slovo z 'data' obsahuje indexy, na ktorych sa slovo v 'data' nachadza)

    VSTUPNE PODMIENKY:
        'data' moze obsahovat lubobolny pocet slov
        'data' moze obsahovat opakujuce sa slova
        slova mozu byt prazdne retazce

    VYSTUPNE PODMIENKY:
        Index obsahuje zoznamy vyskytov len pre slova, ktore sa nachadzaju v 'data'

    PRIKLADY:
        vstup: data = ("pocitac", "lietadlo", luk", "pocitac", "pocitac", "okno", "luk")
        vystup: {"pocitac" -> {0, 3, 4}, "lietadlo" -> {1}, "luk" -> {2, 6}, "okno" -> {5}}

        vstup: data = ("pocitac", "")
        vystup: {"pocitac" -> {0}, "" -> {1}}

        vstup: data = ()
        vystup: {}
*/

map<string, set<size_t>> index(const vector<string> & data) noexcept {
    map<string, set<size_t>> result;
    for (size_t i = 0; i < data.size(); ++i) {
        // Vložíme do mapy slovo a jeho index
        result[data[i]].insert(i);
    }
    return result; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------

// tu mozete doplnit pomocne funkcie a struktury

int main() {

    // tu mozete doplnit testovaci kod
    Node *node2 = new Node(2);
    Node *node7 = new Node(7);
    Node *node5 = new Node(5, node2, node7);

    Node *node20 = new Node(20);
    Node *node15 = new Node(15, nullptr, node20);

    Node *root = new Node(10, node5, node15);

    // Vytvorenie stromu
    BinarySearchTree tree(root);
    int uloha1;
    uloha1=min(&tree);
    int uloha2;
    uloha2=depth(&tree,15);

    Node *n1 = new Node(40);
    Node *n2 = new Node(20);
    Node *n3 = new Node(50);
    Node *n4 = new Node(10);
    Node *n5 = new Node(30);
    Node *n6 = new Node(60);

    // Prepojenie uzlov podľa štruktúry stromu
    n1->smaller = n2;
    n1->greater = n3;
    n2->smaller = n4;
    n2->greater = n5;
    n3->greater = n6;

    // Vytvorenie stromu
    BinarySearchTree treee(n1);

    list<int> uloha3=path(&treee,45);

    size_t uloha4;
    uloha4= count(&treee);

    list<int> uloha5=all(&treee);
    size_t uloha6=countGreater(&treee,20);

    clear(&treee);

    std::vector<int> numbers = {100, 102, 104, 106, 108, 110};
    size_t uloha7= contains(numbers,104);

    vector<string> data1 = {"pocitac", "lietadlo", "luk", "pocitac", "pocitac", "okno", "luk"};
    map<string, set<size_t>> result= index(data1) ;


    return 0;
}
