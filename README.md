# Documentatie proiect POO - Sistem de compresie si decompresie

## 1. Introducere si descriere

Sistemul reprezinta o aplicatie destinata comprimarii si decomprimarii fisierelor. Aplicatia se foloseste de urmatorii doi algoritmi:
1. **Algoritmul Huffman**
2. **Algoritmul LZW**

## 2. Optiuni pentru user

La rularea programului, userul are disponibile urmatoarele 5 optiuni, codificate de la 1 la 5:
1. Arhivare folosind Huffman
2. Arhivare folosind LZW
3. Arhivare folosind algoritmul optim pentru fisierul dat (Programul compara rezultatele celor doi algoritmi si alege fisierul cu dimensiunea cea mai mica)
4. Dezarhiveaza un fisier (.bin)
5. Afiseaza statistici si iesi (Programul afiseaza cati bytes a economisit pe parcursul rularii si se opreste)

La arhivare si dezarhivare, user-ului ii este ceruta o parola. Pentru a nu seta o parola, user-ul poate apasa Enter. 

Parola functioneaza in urmatorul mod: 
-> user-ul furnizeaza o parola
-> peste parola este aplicata o functie ireversibila, rezultand o variabila pe 32 de biti valoare
-> peste variabila valoare este aplicata o noua functie ireversibila, rezultand variabila2.
Variabila2 este retinuta in header.

Variabila Valoare este data ca seed catre un randomizer determinist si apoi fiecare bucket de 8 biti scris pe disc urmeaza sa fie xor-at cu urmatoarea valoare generata de randomizer

Cand se verifica daca parola este corecta, se aplica din nou functiile ireversibile peste ceea ce user-ul a furnizat.

