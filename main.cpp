#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

struct Nod {
    Nod* parinte;
    Nod* copil;
    Nod* stanga;
    Nod* dreapta;
    int cheie;
    int grad;
    int marcare;
    int c;
};

struct Nod* minim[100];

int n[100], m = 0;

void InsereazaNod(int val, int i){
    struct Nod* newNod = (struct Nod*)malloc(sizeof(struct Nod));
    newNod->parinte = NULL;
    newNod->copil = NULL;
    newNod->stanga = newNod;
    newNod->dreapta = newNod;
    newNod->cheie = val;
    newNod->grad = 0;
    newNod->marcare = 0;
    newNod->c = 0;
    if(minim[i] != NULL){
        (minim[i]->stanga)->dreapta = newNod;
        newNod->dreapta = minim[i];
        newNod->stanga = minim[i]->stanga;
        minim[i]->stanga = newNod;
        if(newNod->cheie < minim[i]->cheie){
            minim[i] = newNod;
        }
    }
    else{
        minim[i] = newNod;
    }
}
void Consolideaza(int i);

void ConstruiesteHeap(int i){
    int x;//[101];
    cin>>n[i];
    for(int c=0; c<n[i]; c++){
        cin>>x;
        InsereazaNod(x, i);
    }
    Consolideaza(i);
    m++;
}


void Conectare(struct Nod* ptr2, struct Nod* ptr1, int i) {
    (ptr2->stanga)->dreapta = ptr2->dreapta;
    (ptr2->dreapta)->stanga = ptr2->stanga;
    if (ptr1->dreapta == ptr1)
        minim[i] = ptr1;
    ptr2->stanga = ptr2;
    ptr2->dreapta = ptr2;
    ptr2->parinte = ptr1;
    if (ptr1->copil == NULL)
        ptr1->copil = ptr2;
    ptr2->dreapta = ptr1->copil;
    ptr2->stanga = (ptr1->copil)->stanga;
    ((ptr1->copil)->stanga)->dreapta = ptr2;
    (ptr1->copil)->stanga = ptr2;
    /*
    ///seteaza conexiunea parinte copil intre nodul parinte si copilul cu cea mai mica cheie
    if (ptr2->cheie < (ptr1->copil)->cheie)
        ptr1->copil = ptr2;
    */
    ptr1->grad++;
}


void Consolideaza(int i){
    int temp1;
    float temp2 = (log(n[i])) / (log(2));
    int temp3 = temp2;
    struct Nod* vec[temp3];
    for (int i = 0; i <= temp3; i++)
        vec[i] = NULL;
    Nod* ptr1 = minim[i];
    Nod* ptr2;
    Nod* ptr3;
    Nod* ptr4 = ptr1;
    do {
        ptr4 = ptr4->dreapta;
        temp1 = ptr1->grad;
        while (vec[temp1] != NULL) {
            ptr2 = vec[temp1];
            if (ptr1->cheie > ptr2->cheie) {
                ptr3 = ptr1;
                ptr1 = ptr2;
                ptr2 = ptr3;
            }
            if (ptr2 == minim[i])
                minim[i] = ptr1;
            Conectare(ptr2, ptr1, i);
            if (ptr1->dreapta == ptr1)
                minim[i] = ptr1;
            vec[temp1] = NULL;
            temp1++;
        }
        vec[temp1] = ptr1;
        ptr1 = ptr1->dreapta;
    } while (ptr1 != minim[i]);
    minim[i] = NULL;
    for (int j = 0; j <= temp3; j++) {
        if (vec[j] != NULL) {
            vec[j]->stanga = vec[j];
            vec[j]->dreapta = vec[j];
            if (minim[i] != NULL) {
                (minim[i]->stanga)->dreapta = vec[j];
                vec[j]->dreapta = minim[i];
                vec[j]->stanga = minim[i]->stanga;
                minim[i]->stanga = vec[j];
                if (vec[j]->cheie < minim[i]->cheie)
                    minim[i] = vec[j];
            }
            else {
                minim[i] = vec[j];
            }
            if (minim[i] == NULL)
                minim[i] = vec[j];
            else if (vec[j]->cheie < minim[i]->cheie)
                minim[i] = vec[j];
        }
    }
}


void ExtrageMin(int i) {
    if (minim[i] == NULL)
        cout << "Heap-ul este gol." << endl;
    else {
        Nod* temp = minim[i];
        Nod* pntr;
        pntr = temp;
        Nod* x = NULL;
        if (temp->copil != NULL) {
            x = temp->copil;
            do {
                pntr = x->dreapta;
                (minim[i]->stanga)->dreapta= x;
                x->dreapta = minim[i];
                x->stanga = minim[i]->stanga;
                minim[i]->stanga = x;
                if (x->cheie < minim[i]->cheie)
                    minim[i] = x;
                x->parinte = NULL;
                x = pntr;
            } while (pntr != temp->copil);
        }
        (temp->stanga)->dreapta = temp->dreapta;
        (temp->dreapta)->stanga = temp->stanga;
        minim[i] = temp->dreapta;
        if (temp == temp->dreapta && temp->copil == NULL)
            minim[i] = NULL;
        else {
            minim[i] = temp->dreapta;
            Consolideaza(i);
        }
        n[i]--;
    }
}


void Taie(struct Nod* aux, struct Nod* temp, int i) {
    if (aux == aux->dreapta)
        temp->copil = NULL;
    (aux->stanga)->dreapta = aux->dreapta;
    (aux->dreapta)->stanga = aux->stanga;
    if (aux == temp->copil)
        temp->copil = aux->dreapta;
    temp->grad = temp->grad - 1;
    aux->dreapta = aux;
    aux->stanga = aux;
    (minim[i]->stanga)->dreapta = aux;
    aux->dreapta = minim[i];
    aux->stanga = minim[i]->stanga;
    minim[i]->stanga = aux;
    aux->parinte = NULL;
    aux->marcare = 1;
}


void TaieRec(struct Nod* temp, int i) {
    Nod* ptr = temp->parinte;
    if (ptr != NULL) {
        if (temp->marcare == 0) {
            temp->marcare = 1;
        }
        else {
            Taie(temp, ptr, i);
            TaieRec(ptr, i);
        }
    }
}


void DescresteCheie(struct Nod* aux, int val, int i) {
    if (minim[i] == NULL) {
        cout << "Heap-ul este gol." << endl;
    }else {
        if (aux == NULL)
        cout << "Nodul nu a fost gasit in Heap." << endl;
    }
    aux->cheie = val;
    struct Nod* temp = aux->parinte;
    if (temp != NULL && aux->cheie < temp->cheie) {
        Taie(aux, temp, i);
        TaieRec(temp, i);
    }
    if (aux->cheie < minim[i]->cheie)
        minim[i] = aux;
}


void GasesteNod(struct Nod* mini, int oldVal, int val, int i, Nod* &poz) {
    struct Nod* aux = NULL;
    Nod* temp = mini;
    temp->c = 1;
    Nod* ptr = NULL;
    if (temp->cheie == oldVal) {
        ptr = temp;
        temp->c = 0;
        aux = ptr;
        poz = ptr;
        DescresteCheie(aux, val, i);
    }
    if (ptr == NULL) {
        if (temp->copil != NULL)
            GasesteNod(temp->copil, oldVal, val, i, poz);
        if ((temp->dreapta)->c != 1)
            GasesteNod(temp->dreapta, oldVal, val, i, poz);
    }
    temp->c = 0;
    aux = ptr;
}


void Uneste(int i, int j){
    Nod *ptraux;
    int ok;
    if(minim[i] != NULL && minim[j] != NULL){
        do{
            ok = 0;
            if(minim[j]->stanga == minim[j])
                ok = 1;
            else ptraux = minim[j]->stanga->stanga;

            minim[j]->stanga->stanga->dreapta = minim[j];
            minim[j]->stanga->stanga = minim[i]->stanga;
            if(ok != 1){
                minim[j]->stanga->dreapta = minim[i];
                minim[i]->stanga->dreapta = minim[j]->stanga;
                minim[i]->stanga = minim[j]->stanga;
                minim[j]->stanga = ptraux;
                ptraux = NULL;
            }else{
                minim[j]->dreapta = minim[i];
                minim[i]->stanga->dreapta = minim[j];
                minim[i]->stanga = minim[j];
            }
        }while(minim[i]->stanga != minim[j]);
        if(minim[i]->cheie > minim[j]->cheie)
            minim[i] = minim[j];
        minim[j] = NULL;
        n[i] = n[i] + n[j];
        n[j] = 0;
        m--;
    }else cout<<"Heap-urile nu s-au putut reuni deoarece cel putin unul dintre ele este inexistent."<<endl;
    Consolideaza(i);
}


void Afis(struct Nod* minim, int i) {
    Nod* ptr = minim;
    if (ptr == NULL) {
        cout << "Heap-ul este gol." << endl;
    }
    else {
        cout << "Nodurile radacina ale Heap-ului sunt: " << endl;
        do {
            cout << ptr->cheie;
            ptr = ptr->dreapta;
            if (ptr != minim) {
                cout << "-->";
            }
        } while (ptr != minim && ptr->dreapta != NULL);
        cout << endl << "Heap-ul are " << n[i] << " noduri. "<< endl;
    }
}


void StergeNod(int val, int i) {
    if (minim[i] == NULL)
        cout << "Heap-ul este gol." << endl;
    else {
        Nod *x;
        GasesteNod(minim[i], val, 0, i, x);
        ExtrageMin(i);
        cout << "Cheia a fost stearsa." << endl;
    }
}


void CautaMin(int i) {
    if(minim[i]->cheie != NULL)
        cout << "Minimul Heap-ului este: " << minim[i]->cheie << endl;
    else cout << "Heap-ul nu are minim deoarece este gol."<<endl;
}

int main()
{
    int i, j, l = 1, k, ok;
    Nod* poz;
    cout<<"Introduce-ti numarul de noduri ale Heap-ului urmat de valorile nodurilor:\n(folositi enter intre numarul de noduri si space intre fiecare nod) \n";
    ConstruiesteHeap(l);
    Afis(minim[l], l);
    cout<<"Aceste este primul Heap.\n";
    CautaMin(l);
    cout<<endl;
    do {
        cout<<"1 -> Crearea unui nou Heap\n"
            <<"2 -> Inserarea elementului de valoare k in al i-lea Heap\n"
            <<"3 -> Stergerea nodului de valoare k din al i-lea Heap\n"
            <<"4 -> Stergerea nodului de valoare minima din al i-lea Heap\n"
            <<"5 -> Unirea celui de-al i-lea Heap cu cel de-al j-lea Heap\n"
            <<"6 -> Optiunea de oprire\n";

        cout<<"Introduceti o optiune:\n";
        cin>>ok;
        switch(ok) {
        case 1:
            cout<<"Introduce-ti numarul de noduri ale Heap-ului urmat de valorile nodurilor:\n(folositi enter intre numarul de noduri si space intre fiecare nod) \n";
            l++;
            ConstruiesteHeap(l);
            cout<<"Aceste este cel de-al "<<l<<"-lea Heap.\n\n";
            Afis(minim[l], l);
            cout<<endl;
            break;
        case 2:
            cout<<"k = ";
            cin>>k;
            cout<<"i = ";
            cin>>i;
            poz = NULL;
            GasesteNod(minim[i], k, 0, i, poz);
            if(i > l)
                cout<<"Nu exista un al "<<i<<"-lea Heap.\n";
            else
                if(minim[i] == NULL)
                    cout<<"Al "<<i<<"-lea Heap nu mai exista ca rezultat al operatiilor efectuate anterior.\n";
                else {
                    if(poz == NULL){
                        InsereazaNod(k, i);
                        Afis(minim[i], i);
                    }else cout<<"Nodul cu valoarea "<<k<<" deja exista in al "<<i<<"-lea Heap.\n";
                }
            cout<<endl;
            break;
        case 3:
            cout<<"k = ";
            cin>>k;
            cout<<"i = ";
            cin>>i;
            poz = NULL;
            GasesteNod(minim[i], k, 0, i, poz);
            if(i > l)
                cout<<"Nu exista un al "<<i<<"-lea Heap.\n";
            else
                if(minim[i] == NULL)
                    cout<<"Al "<<i<<"-lea Heap nu mai exista ca rezultat al operatiilor efectuate anterior.\n";
                else {
                    if(poz != NULL){
                        StergeNod(k, i);
                        Afis(minim[i], i);
                    }else cout<<"Nodul cu valoarea "<<k<<" nu exista in al "<<i<<"-lea Heap.\n";
                }
            cout<<endl;
            break;
        case 4:
            cout<<"i = ";
            cin>>i;
            CautaMin(i);
            ExtrageMin(i);
            Afis(minim[i], i);
            CautaMin(i);
            cout<<endl;
            break;
        case 5:
            if(l == 1)
                cout<<"Nu sunt destule Heap-uri pentru a face o Unire.\n";
            else{
                cout<<"i = ";
                cin>>i;
                cout<<"j = ";
                cin>>j;
                if(i > l)
                    cout<<"Nu exista un al "<<i<<"-lea Heap.\n";
                else
                    if(minim[i] == NULL)
                        cout<<"Al "<<i<<"-lea Heap nu mai exista ca rezultat al operatiilor efectuate anterior.\n";
                    else
                        if(j > l)
                            cout<<"Nu exista un al "<<j<<"-lea Heap\n";
                        else
                            if(minim[j] == NULL)
                                cout<<"Al "<<j<<"-lea Heap nu mai exista ca rezultat al operatiilor efectuate anterior.\n";
                            else {
                                Uneste(i, j);
                                Afis(minim[i], i);
                                CautaMin(i);
                                cout<<"Heap-ul format din cele doua Heap-uri va fi al "<<i<<"-lea Heap.\n";
                            }
            }
            cout<<endl;
            break;
        case 6:
            ok = 0;
            cout<<"Rularea programului a luat sfarsit.";
            break;
        default:
            cout<<"Numarul acesta nu corespunde unei optiuni.\n";
            cout<<endl;
            ok=1;
        }
    }while(ok != 0);
    return 0;
}
