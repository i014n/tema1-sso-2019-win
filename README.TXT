1.Introducere
	Programul are baza ideea implementarii unei cozi de prioritati.
	Asupra cozii se pot face unele dintre operatiile : 
		1)insert(nume, prioritate), adauga elemente noi
		2)top(), intoarce primul element
		3)pop(), elimina primul element
	Operatiile pot fi citite de tastaura pana la intalnirea caracterului EOF sau din fisiere.

2. Idee de implementare
		Principala problema a fost cea legata de inserarea unui nou element. Pentru acesta operatie este necesar cunoasterea locului unde trebuie introdus si deplasarea dupa a celorlate elemente daca exista.
	Acesta functionalitate a fost implementata cu ajutorul functie "move_to_right( element_Start, nume, prioritate).
	Functia deplaseaza toate elementele catre "dreapta", practic incepand cu elementul "element_Start" toate elementele sunt duplicare in urmatorul element, ultimul urmand sa creat si alocat.
	"Move_to_right(element_Start,name,prioritare)" este apelata de obicei in functia de inserare.
	Functia de inserare, gaseste primul element cu prioritare mai mica decat elementul ce trebuie inserat, iar pe baza elementului gasit se aplica functia de mai sus.
		O alta problema in cadrul implementarii au fost citirea si validarea opearatiilor asupra cozii.
	Pentru citire, am ales o implementare citind cate un caracter pana la intalnirea NEW_LINE. Acest caracter urmand dupa aceea a fi copiat intr-un buffer care se resetea dupa intalnirea caracterului NEW_LINE.
	Acest lucru este implementat cu ajutorul functie "read_comand(nume_comanda)". 
	Validarea comenzii a presupus, in ideea mea, doua functii ce ajuta la protectia si validarea opearatiilor asupra cozii.
	Prima functie "get_operation_code" ajuta la modularizare programului verificand rapid daca operatia exista.
	Cea de-a doua functie de protectie este "prepare_insert" care valideaza datele necare operatie dorite.
		
3. Bine de stiut
		Pentru usurarea,asigurea ca datele sunt valide si eviterea duplicarii codului am implentat functii ce au ca scop usurarea unor operatii uzuale:
			1)creare/alocarea elementele (queue_alloc)
			2)copierea elementelor (duplicare_element)
			3)eliberarea resurselor de memorie in cazul stergerii unui element al cozii(my_free)
			4)eliberarea si incheirea executie programului in cazul unei erori provenite la incapacitatea alocarii zonelor de memorie
			