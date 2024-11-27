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
(8)  Vase riesenie otestujte (vo funkcii 'main' a pomocou doplnenych pomocnych funkcii alebo datovych typov).
     Testovaci kod ale nebude hodnoteny.
(9)  Funkcia 'main' musi byt v zdrojovom kode posledna.
*/

#include <iostream>
#include <cstring>

using namespace std;

//-------------------------------------------------------------------------------------------------
// DATOVE TYPY
//-------------------------------------------------------------------------------------------------

// Uzol zretazeneho zoznamu
struct Node {
    int data; // hodnota uzla
    Node* next; // smernik na dalsi uzol zoznamu
};

// Zretazeny zoznam
struct List {
    Node* first; // smernik na prvy uzol zoznamu
};

//-------------------------------------------------------------------------------------------------
// 1. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada pole 'data' od najvacsieho prvku po najmensi prvok.
    Pouzite algoritmus insertion sort.

    PARAMETRE:
        [in, out] data - pole, ktore funkcia usporiada
        [in] length    - pocet prvkov pola

    VSTUPNE PODMIENKY:
        'length' moze mat lubovolnu hodnotu
        'data' ukazuje na platne pole

    PRIKLADY:
        (1, 3, 2) -> (3, 2, 1)
        (1, 2, 2, 1) -> (2, 2, 1, 1)
        (1) -> (1)
        () -> ()
*/
void insertionSort(int *data, const size_t length) {
    for(size_t i=1;i<length;i++){
        int temp=data[i];
        size_t j=i;
        while(j>0 && data[j-1]<temp){
            data[j]=data[j-1];
            j--;
        }
        data[j]=temp;
    }
}

//-------------------------------------------------------------------------------------------------
// 2. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada textove retazce v poli 'data' od najvacsieho prvku po najmensi (lexikograficky).
    Preusporiadajte smerniky v poli.
    Pouzite algoritmus insertion sort.

    PARAMETRE:
        [in, out] data - pole, ktore funkcia usporiada.
                Pole obsahuje smerniky na textove retazce.
                Kazdy textovy retazec je ukonceny '\0'.
                Posledny smernik ma hodnotu 'nullptr'. Podla toho urcite pocet prvkov pola (pocet textovych retazcov).

    VSTUPNE PODMIENKY:
        'data' obsahuje minimalne jeden smernik.
        Posledny smernik ma hodnotu 'nullptr'.

    PRIKLADY:
        ("Juraj", "Peter", "Andrej", nullptr) -> ("Peter", "Juraj", "Andrej", nullptr)
        ("Juraj", "Anabela", "Peter", "Andrej", nullptr) -> ("Peter", "Juraj", "Andrej", "Anabela", nullptr)
        ("Andrej", "Juraj", "Andrej", nullptr) -> ("Juraj", "Andrej", "Andrej", nullptr)
        ("Andrej", nullptr) -> ("Andrej", nullptr)
        (nullptr) -> (nullptr)

    POZNAMKY:
        Pri testovani mozete jednoducho pole vytvorit nasledovnym sposobom:
        const char *mena[] = {"Juraj", "Peter", "Andrej", nullptr};

        Na porovnanie obsahu textovych retazcov vyuzite prislusnu funkciu zo standardnej kniznice.
*/
void insertionSort(const char *data[]) {
    size_t i=1;
    if(data[0]!= nullptr){
        while(data[i]!= nullptr){
            const char* temp=data[i];
            size_t j=i;
            while(j>0 && 0<std::strcmp(temp,data[j-1])){
                data[j]=data[j-1];
                j--;
            }
            data[j]=temp;
            i++;
        }
    }
}

//-------------------------------------------------------------------------------------------------
// 3. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada zretazeny zoznam 'list' od najvacsieho prvku po najmensi.
    Preusporiadajte uzly v zozname (nekopirujte hodnoty v uzloch).
    Pouzite algoritmus insertion sort.

    PARAMETRE:
        [in, out] list - zretazeny zoznam, ktory funkcia usporiada

    VSTUPNE PODMIENKY:
        'list' obsahuje lubovolny pocet uzlov (moze byt prazdny)
        'list' nie je 'nullptr'

    PRIKLADY:
        vstup: 2->1->3,        vystup: 3->2->1
        vstup: 1->2->2->1,     vystup: 2->2->1->1
        vstup: prazdny zoznam, vystup: prazdny zoznam
*/
/*
Node* predchadzajuci_node(List*list,Node* node){
    Node* nodee=list->first;
    if(node==list->first){
        return nullptr;
    }
    while(nodee!= nullptr){
        if(nodee->next==node){
            return nodee;
        }
        nodee=nodee->next;
    }
}*/
void insertionSort(List* list) {
    if (list->first == nullptr) return;  // Ak je zoznam prázdny, nič nerobíme
    Node* sorted = nullptr;  // Zoradený zoznam (začneme s prázdnym)
    Node* current = list->first;

    while (current != nullptr) {
        Node* next = current->next;  // Uložíme nasledujúci uzol

        // Nájdeme miesto na vloženie aktuálneho uzla do zoradeného zoznamu
        if (sorted == nullptr || sorted->data <= current->data) {
            // Vkladáme na začiatok zoradeného zoznamu
            current->next = sorted;
            sorted = current;
        } else {
            // Nájdeme správne miesto na vloženie do zoradeného zoznamu
            Node* temp = sorted;
            while (temp->next != nullptr && temp->next->data > current->data) {
                temp = temp->next;
            }
            // Vložíme aktuálny uzol medzi temp a temp->next
            current->next = temp->next;
            temp->next = current;
        }

        current = next;  // Posunieme sa na ďalší uzol v pôvodnom zozname
    }

    // Nastavíme zoznam na zoradený zoznam
    list->first = sorted;
}

/*
void insertionSort(List* list){
    Node* start=list->first;
    Node*current=start;
    Node*dalsi;
    int i=0;
    if(current!= nullptr){
        dalsi=current->next;
        start->next= nullptr;
        while(dalsi!= nullptr){
            current=dalsi;
            dalsi=dalsi->next;
            i++;
            Node* temp=start;
            Node* predtemp;
            while(temp!= nullptr){
                //predtemp=temp;
                if(current->data>temp->data){
                    break;
                }
                predtemp=temp;
                temp=temp->next;
            }
            if(temp==start){
                Node* zapametaj=start;
                start=current;
                current->next=zapametaj;
            }
            else if(temp== nullptr){
                predtemp->next=current;
                current->next= nullptr;
            }
            else{
                Node* zapametaj=temp;

                temp=current->next;
                current->next=zapametaj;
            }
        }
        list->first=start;
    }
}*/
/*
void insertionSort(List * list) {
    Node* node=list->first;
    if(node!= nullptr){
        node=node->next;
    }
    while(node!= nullptr){
        Node *temp=list->first;
        while(temp->next!=node && temp->data>node->data){
            temp=temp->next;
        }
        Node*pred= predchadzajuci_node(list,node);
        pred->next=node->next;
        if(temp==list->first){
            list->first=node;
        }
        else{
            Node*predd=predchadzajuci_node(list,temp);
            predd->next=node;
        }
        node->next=temp;
        node=pred->next;
    }
}*/

//-------------------------------------------------------------------------------------------------
// 4. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vykona algoritmus merge (cast algoritmu merge sort), ktory ma linearnu vypoctovu zlozitost.
    Kombinuje dve susedne, usporiadane casti v poli 'input', do jednej usporiadanej casti v poli 'output'.
    Usporiadanie je od najvacsieho prvku po najmensi prvok!

    PARAMETRE:
        [out] output - vystupne pole, ktoreho cast output[low]...output[high-1] bude po vykonani funkcie usporiadana
        [in]  input  - vstupne pole, ktoreho casti input[low]...input[middle-1] a input[middle]...input[high-1]
                         musia byt pri volani funkcie usporiadane od najvacsieho prvku po najmensi
        [in]  low    - index 1. prvku lavej usporiadanej casti pola 'input'
        [in]  middle - index 1. prvku pravej usporiadanej casti pola 'input'
        [in]  high   - index za poslednym prvkom pravej usporiadanej casti pola 'input'

    VYSTUPNE PODMIENKY:
        Obsah 'input' je nezmeneny.
        output[low] ... output[high-1] obsahuje usporiadane prvky z input[low] ... input[high-1].
        Prvky s indexami mensimi ako 'low' sa nemenia (ani v jednom poli).
        Prvky s indexami vacsimi alebo rovnymi ako 'high' sa nemenia (ani v jednom poli).

    PRIKLAD:
        low: 4
        middle: 8
        hight: 12
        input:                         (10, 10, 10, 10,  7,  5,  2,  0,  8,  4,  2,  1, 10, 10, 10, 10)
        output pred vykonanim funkcie: (20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20)
        output po vykonani funkcie:    (20, 20, 20, 20,  8,  7,  5,  4,  2,  2,  1,  0, 20, 20, 20, 20)
*/
void mergeNeighbours(int *output, const int *input, size_t low, size_t middle, size_t high) {
    size_t in1 = low;
    size_t in2 = middle;
    size_t out = low;

    while (in1 < middle && in2 < high) {
        if (input[in1] >= input[in2]) { // stabilne triedenie
            output[out] = input[in1];
            ++ in1;
        }
        else {
            output[out] = input[in2];
            ++ in2;
        }
        ++ out;
    }
    while (in1 < middle) {
        output[out] = input[in1];
        ++ in1;
        ++ out;
    }
    while (in2 < high) {
        output[out] = input[in2];
        ++ in2;
        ++ out;
    }
}/*
void mergeNeighbours(int *output, const int *input, const size_t low, const size_t middle, const size_t high) {
    size_t a=0,b=0,i=0;
    while(b+middle<high && a+low<middle){
        if(input[low+a]>=input[middle+b]){
            output[low+i]=input[low+a];
            a++;
        }
        else{
            output[low+i]=input[middle+b];
            b++;
        }
        i++;
    }
    while((i+low)<high){
        output[i+low]=input[low+a];
        i++;a++;
    }

    while((i+low)<high){
        output[i+low]=input[low+b];
        i++;b++;
    }

}
*/
//-------------------------------------------------------------------------------------------------
// 5. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada prvky v poli 'data' od najvacsieho prvku po najmensi.
    Pouzite algoritmus merge sort.
    Vytvorte jedno pomocne pole. Pre alokaciu a dealokaciu pomocneho pola pouzite new[] a delete[].

    PARAMETRE:
        [in, out] data - pole, ktore funkcia usporiada
        [in] length    - pocet prvkov pola

    VSTUPNE PODMIENKY:
        'data' ukazuje na platne pole

    PRIKLADY:
        (1, 3, 2) -> (3, 2, 1)
        (1, 2, 2, 1) -> (2, 2, 1, 1)
        (1) -> (1)
        () -> ()

    POZNAMKA:
        Ak pouzijete pristup top-down, tak
        - v tejto funkcii zabezpecte vytvorenie a kopirovanie dat do pomocneho pola,
        - vytvorte a zavolajte rekurzivnu funkciu, v ktorej implementujete hlavnu cast algoritmu merge sort.
*/
void println(const char *label, const int *data, size_t length) {
    std::cout << label << ": ";
    for (size_t i = 0; i < length; ++ i) {
        std::cout<< data[i] << " ";
    }
    std::cout << std::endl;
}

void mergeSort(int *data, const size_t length) {
    size_t high=1;
    size_t i=0;
    int treba=-1;
    int*temp;
    int *docasny=new int[length];
    int*output=docasny;
    while(high<length){
        while(i<length){
            size_t middle=(i+high>length)?length:i+high;
            size_t highh=(i+2*high>length)?length:i+2*high;
            mergeNeighbours(output,data,i,middle,highh);
            i+=2*high;
        }
        high*=2;
        i=0;
        temp=output;
        output=data;
        data=temp;
        treba*=-1;
    }
    if(treba>0){
        std::memcpy(output,data,length*sizeof(int));
    }
    delete[] docasny;
}

//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------

// tu mozete doplnit pomocne funkcie a struktury

Node* createnode(const int data){
    Node*tmp=new Node;
    tmp->data=data;
    tmp->next= nullptr;
    return tmp;
}

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

List* createListFromArray(const int* data, const size_t n) {
    List* listy=new List;
    listy->first= nullptr;
    for(int i=0;i<n;i++){
        appendNode(listy,data[i]);
    }
    return listy; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

int main() {
    int data[6]={1,3,2,4,44,66};
    insertionSort(data,6);
    // tu mozete doplnit testovaci kod
    const char *mena[] = {"Juraj", "Anabela", "Peter", "Andrej", nullptr};
    insertionSort(mena);
    int data4[8]={8,3,5,2};
    List* list4=createListFromArray(data4,4);
    insertionSort(list4);


    int low=4,high=12,middle=8;
    int input[]={10, 10, 10, 10,  7,  5,  2,  0,  8,  4,  2,  1, 10, 10, 10, 10};
    int output[]={20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20};
    mergeNeighbours(output,input,low,middle,high);
    int inpuut[]={1,2,45,47,3,4,5};
    mergeSort(inpuut,2);
    //println("output ",inpuut,2);
    return 0;
}
