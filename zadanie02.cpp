/*
Meno a priezvisko:Branislav Jurko

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
(8)  Vase riesenie otestujte (vo funkcii 'main' a pomocou doplnenych pomocnych funkcii alebo datovych typov).
     Testovaci kod ale nebude hodnoteny.
(9)  Funkcia 'main' musi byt v zdrojovom kode posledna.
*/


#include <iostream>

using namespace std;

//-------------------------------------------------------------------------------------------------
// DATOVE TYPY
//-------------------------------------------------------------------------------------------------

// Reprezentacia uzla zretazeneho zoznamu
struct Node {
    int data; // hodnota uzla
    Node* next; // adresa nasledujuceho uzla zoznamu
};

// Reprezentacia zretazeneho zoznamu
struct List {
    Node* first; // adresa prveho uzla zoznamu
};

// Uspesnost vykonania funkcie
enum class Result {
    SUCCESS, // funkcia vykonana uspesne
    FAILURE  // chyba pri vykonavani funkcie
};

//-------------------------------------------------------------------------------------------------
// 1. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia prida novy uzol s hodnotou 'val' na zaciatok zoznamu 'list'.

    PARAMETRE:
        [in] list - vstupny zretazeny zoznam
        [in] val - hodnota uzla pridaneho na zaciatok zoznamu

    PRIKLADY:
        list=() a val=0 ... zoznam po vykonani funkcie ... (0)
        list=(-3) a val=1 ... zoznam po vykonani funkcie ... (1,-3)
        list=(6,6,5,8) a val=10 ... zoznam po vykonani funkcie ... (10,6,6,5,8)
*/

Node* createnode(const int data){
    Node*tmp=new Node;
    tmp->data=data;
    tmp->next= nullptr;
    return tmp;
}

void prependNode(List* list, const int val) {
    Node* tmp= createnode(val);
    tmp->next=list->first;
    list->first=tmp;
}

//-------------------------------------------------------------------------------------------------
// 2. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia prida novy uzol s hodnotou 'val' na koniec zoznamu 'list'.

    PARAMETRE:
        [in] list - vstupny zretazeny zoznam
        [in] val - hodnota uzla pridaneho na koniec zoznamu

    PRIKLADY:
        list=() a val=7 ... zoznam po vykonani funkcie ... (7)
        list=(0) a val=1 ... zoznam po vykonani funkcie ... (0,1)
        list=(1,2,3,4,5) a val=6 ... zoznam po vykonani funkcie ... (1,2,3,4,5,6)
*/

void appendNode(List* list, const int val) {
    Node*tmp= createnode(val);
    if(list->first){
        Node*tmp2=list->first;
        while(tmp2->next){
            tmp2=tmp2->next;
        }
        tmp2->next=tmp;
    }
    else{
        list->first=tmp;
    }
}

//-------------------------------------------------------------------------------------------------
// 3. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori novy zretazeny zoznam a vyplni ho vsetkymi cislami (v zachovanom poradi),
    ktore sa nachadzaju vo vstupnom poli 'data', ktore ma dlzku 'n'.

    PARAMETRE:
        [in] data - vstupne pole cisiel
        [in] n - dlzka vstupneho pola

    NAVRATOVA HODNOTA:
        Vytvoreny zretazeny zoznam obsahujuci vsetky hodnoty zo vstupneho pola 'data' (v zachovanom poradi).
        V pripade prazdneho pola (dlzka 0), funkcia vrati prazdny zoznam (prazdny zoznam je taky, kde smernik 'first'
        ukazuje na 'nullptr').

    PRIKLADY:
        data=(1) a n=1 ... vrati zoznam ... (1)
        data=(7,6,41,2) a n=4 ... vrati zoznam ... (7,6,41,2)
        data=(3,2,1) a n=0 ... vrati zoznam ... ()
*/

List* createListFromArray(const int* data, const size_t n) {
    List* listy=new List;
    listy->first= nullptr;
    for(int i=0;i<n;i++){
        appendNode(listy,data[i]);
    }
    return listy; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// 4. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori novy symetricky zretazeny zoznam (vid priklady) podla parametra 'val'.
    Symetricky zoznam ma tvar 0,1,2,...val...2,1,0.

    PARAMETRE:
        [in] val - hodnota uzla podla, ktoreho sa vytvori novy symetricky zretazeny zoznam (uzol v strede zoznamu).

    NAVRATOVA HODNOTA:
        Vytvoreny zretazeny zoznam obsahujuci prvky v takom poradi, aby bol symetricky.
        V pripade 'val'<0, funkcia vrati 'nullptr'.

    PRIKLADY:
        val=-31 ... vrati ... nullptr
        val=0 ... vrati zoznam ... (0)
        val=1 ... vrati zoznam ... (0,1,0)
        val=2 ... vrati zoznam ... (0,1,2,1,0)
        val=3 ... vrati zoznam ... (0,1,2,3,2,1,0)
        val=4 ... vrati zoznam ... (0,1,2,3,4,3,2,1,0)
        val=6 ... vrati zoznam ... (0,1,2,3,4,5,6,5,4,3,2,1,0)
*/

List* createSymmetricList(const int val) {
    List* list=new List;
    list->first= nullptr;
    if(val<0){
        return nullptr;
    }
    if(val>=0){prependNode(list,val);}
    for(int i=val-1;i>=0;i--){
        prependNode(list,i);
        appendNode(list,i);
    }
    return list; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// 5. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia odstrani (aj spravne uvolni pamat) zo vstupneho zoznamu 'list' prvy uzol.

    PARAMETRE:
        [in,out] list - zretazeny zoznam, z ktoreho funkcia odstrani uzol

    NAVRATOVA HODNOTA:
        Result::SUCCESS, ak bol prvy uzol vymazany
        Result::FAILURE, ak nebol prvy uzol vymazany (vstupny zoznam bol prazdny)

    PRIKLADY:
        list=() ... funkcia vrati Result::FAILURE
        list=(5) ... zoznam po vykonani funkcie ... () a vrati Result::SUCCESS
        list=(10,10,10) ... zoznam po vykonani funkcie ... (10,10) a vrati Result::SUCCESS
        list=(3,2,1) ... zoznam po vykonani funkcie ... (2,1) a vrati Result::SUCCESS
*/

Result removeFirstNode(List* list) {
    if(list->first){
        Node*tmp=list->first->next;
        delete list->first;
        list->first=tmp;
        return Result::SUCCESS;
    }
    return Result::FAILURE; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// 6. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia najde prvy uzol zretazeneho zoznamu 'list', ktory obsahuje hodnotu 'val'.

    PARAMETRE:
        [in] list - vstupny zretazeny zoznam
        [in] val - hodnota uzla, ktory sa hlada

    NAVRATOVA HODNOTA:
        Funkcia vrati prvy uzol, ktory obsahuje hodnotu 'val'.
        Ak sa taky uzol v zozname nenachadza alebo je vstupny zoznam prazdny, vtedy funkcia vrati 'nullptr'.

    PRIKLADY:
        list=(), val=10 ... funkcia vrati 'nullptr'
        list=(2), val=3 ... funkcia vrati 'nullptr'
        list=(1,2,3,4,5,6), val=-1 ... funkcia vrati 'nullptr'
        list=(1), val=1 ... funkcia vrati uzol s hodnotou 1
        list=(5,9,18), val=9 ... funkcia vrati uzol s hodnotou 9
*/

Node* findNodeInList(List* list, const int val) {
    Node* tmp=list->first;
    while(tmp){
       if(tmp->data==val){
           return tmp;
       }
       tmp=tmp->next;
    }
    return nullptr; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// 7. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia zisti, ci su dva vstupne zoznamy 'list1' a 'list2' rovnake (t.j. rovnako dlhe a obsahujuce
    rovnake hodnoty uzlov v rovnakom poradi).

    PARAMETRE:
        [in] list1 - prvy zretazeny zoznam
        [in] list2 - druhy zretazeny zoznam

    NAVRATOVA HODNOTA:
        'true' - ak su vstupne zoznamy rovnake
        'false' - ak vstupne zoznamy nie su rovnake

    PRIKLADY:
        list1=(1)
        list2=()
        Funkcia vrati 'false'.

        list1=()
        list2=(5,3)
        Funkcia vrati 'false'.

        list1=()
        list2=()
        Funkcia vrati 'true'.

        list1=(1)
        list2=(1)
        Funkcia vrati 'true'.

        list1=(4,-9,2)
        list2=(4,-9,2)
        Funkcia vrati 'true'.

        list1=(3,2,1)
        list2=(1,2,3)
        Funkcia vrati 'false'.

        list1=(2)
        list2=(7,4,5)
        Funkcia vrati 'false'.

        list1=(7,4)
        list2=(7,4,5)
        Funkcia vrati 'false'.
*/

bool areListsEqual(List* list1, List* list2) {
    Node*tmp1=list1->first;
    Node*tmp2=list2->first;
    while(1){
        if(tmp1== nullptr && tmp2== nullptr){return true;}
        if(tmp1== nullptr ||tmp2== nullptr){return false;}
        if(tmp2->data!=tmp1->data){
            return false;
        }
        if(tmp2->data==tmp1->data){
            tmp1=tmp1->next;tmp2=tmp2->next;
        }
    }
    return false; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// 8. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori novy zretazeny zoznam prekopirovanim vsetkych hodnot uzlov vstupneho zoznamu 'list' v obratenom
    poradi.

    PARAMETRE:
        [in] list - vstupny zretazeny zoznam

    NAVRATOVA HODNOTA:
        Zretazeny oznam, ktory vznikne prekopirovanim hodnot uzlov vstupneho zoznamu 'list' v obratenom poradi.

    PRIKLADY:
        list=() ... funkcia vrati ... () t.j. prazdny zoznam
        list=(1) ... funkcia vrati ... (1)
        list=(5,6) ... funkcia vrati ... (6,5)
        list=(8,14,2,3) ... funkcia vrati ... (3,2,14,8)
*/
Node* predosla(List*list,Node*node){
    Node*tmp=list->first;
    while(1){
        if(tmp->next==node){
            return tmp;
        }
        tmp=tmp->next;
    }
}

List* copyListReverse(List* list) {
    Node*tmp=list->first;
    List* listn=new List;
    listn->first= nullptr;
    if(list->first== nullptr){
        return listn;
    }
    while(tmp->next){
        tmp=tmp->next;

    }
    while(tmp!=list->first){
        tmp->next=predosla(list,tmp);
        appendNode(listn,tmp->data);
        tmp=tmp->next;
    }
    appendNode(listn,tmp->data);
    return listn; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// 9. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vyhlada predchodcu zadaneho uzla 'node' vo vstupnom zretazenom zozname 'list'.

    VSTUPNA PODMIENKA:
        Uzol 'node' je vzdy existujucim uzlom vstupneho zoznamu 'list'.

    PARAMETRE:
        [in] list - vstupny zretazeny zoznam
        [in] node - uzol zretazeneho zoznamu 'list', ktoreho predchodcu hladame

    NAVRATOVA HODNOTA:
        Uzol, ktory je predchodcom uzla 'node' v zozname 'list'.
        V pripade hladania predchodcu prveho uzla zoznamu, funkcia vrati 'nullptr'.

    PRIKLADY:
        list=(4)
        node=4
        Funkcia vrati 'nullptr'.

        list=(1,2,3,4,5)
        node=1
        Funkcia vrati 'nullptr'.

        list=(-2,-3,56,4,41)
        node=-3
        Funkcia vrati uzol s hodnotou -2.

        list=(10,54,69,82,6)
        node=6
        Funkcia vrati uzol s hodnotou 82.
*/

Node* findPreviousNode(List* list, Node* node) {
    Node*tmp=list->first;
    if(tmp==node){return nullptr;}
    while(1){
        if(tmp->next==node){
            return tmp;
        }
        tmp=tmp->next;

    }
}

//-------------------------------------------------------------------------------------------------
// 10. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia zduplikuje vsetky uzly vstupneho zoznamu 'list', ktore obsahuju kladnu hodnotu.

    PARAMETRE:
        [in,out] list - vstupny zretazeny zoznam

    PRIKLADY:
        list=() ... po vykonani funkcie ... ()
        list=(3) ... po vykonani funkcie ... (3,3)
        list=(-1,1) ... po vykonani funkcie ... (-1,1,1)
        list=(-8,-9,-13) ... po vykonani funkcie ... (-8,-9,-13)
        list=(1,0,-2,3,-4) ... po vykonani funkcie ... (1,1,0,-2,3,3,-4)
*/
Node* createnode2(const int data,Node* nod){
    Node*tmp=new Node;
    tmp->data=data;
    tmp->next= nod;
    return tmp;
}

void duplicatePositiveNodes(List* list) {
    Node *tmp = list->first;
    if (list->first != nullptr) {
        while (tmp) {
            if (tmp->data > 0) {
                Node *tmp2 = createnode2(tmp->data, tmp->next);
                tmp->next = tmp2;
                tmp=tmp2->next;
            } else{
                tmp=tmp->next;
            }
        }
    }
}


//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------

// tu mozete doplnit pomocne funkcie a struktury pre testovanie

int main() {
    //1.uloha
    List* list=new List;
    list->first= nullptr;
    prependNode(list,10);
    prependNode(list,9);
    //2.uloha
    appendNode(list,11);
    //3.uloha
    int data[4]={1,2,3,4};
    List* list2=createListFromArray(data,0);
    //4.uloha
    List* list3=createSymmetricList(2);
    // tu mozete doplnit vas vlastny testovaci kod
    removeFirstNode(list3);
    //6uloha
    Node* nod=findNodeInList(list3,1);
    //7uloha
    int data4[4]={1,2,3,4};
    List* list4=createListFromArray(data4,4);
    int data5[4]={1,2,3,4};
    List* list5=createListFromArray(data5,4);
    bool a=areListsEqual(list4,list5);
    //8
    List* list8;
    list8=copyListReverse(list5);
    //9
    Node* node1;
    node1=findPreviousNode(list8,list8->first->next);
    //10
    duplicatePositiveNodes(list4);
    return 0;
}
