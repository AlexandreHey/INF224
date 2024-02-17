# INF224 - Alexandre HEYMANN 

Les parties Java et C++ ont été réalisées. Java étant le client et C++ le serveur. 

Avec la télécommande, on peut demander de lister les objects, d'en jouer un et de l'afficher à partir de son nom (list, display [nom] et play [nom]). Il y a trois fichiers de test, images et vidéos, dans le dossier `Data` pour tester le programme.

Je n'ai pas fait la documentation avec Doxygen par manque de temps.

Lancer le serveur d'abord, puis le client, avec ``make run`` dans les bons dossiers (cpp et swing).

## Questions C++
### Etape 4
*Comment appelle-t'on ce type de méthode et comment faut-il les déclarer ?*

C'est une classe abstraite qui est une classe qui ne peut pas être instanciée directement, mais qui sert de modèle pour d'autres classes qui en héritent.

C'est une méthode virtuelle pure car elle n'a pas de définition dans la classe de base. Elle est donc obligatoire à implémenter dans les classes filles.
La méthode afficher doit être déclarée comme virtuelle pure dans la classe de base.Pour cela on utilise le mot-clé 'virtual' suivi de = 0 dans la déclaration de la méthode, comme ceci :
`virtual void afficher() const = 0;`

### Etape 5
*Quelle est la propriété caractéristique de l'orienté objet qui permet de faire cela ?*

La propriété caractéristique de l'orienté objet qui permet de traiter des objets de types différents de manière uniforme est le polymorphisme (permet à une méthode d'être appelée sur des objets de différentes classes). On appelle la méthode de la classe fille et non de la mère.

*Qu'est-il spécifiquement nécessaire de faire dans le cas du C++ ?*

Dans le cas du C++, il est nécessaire de déclarer la méthode comme virtuelle dans la classe de base. Ici on appelle `play()` de la classe `Multimédia`. 

*Quel est le type des éléments du tableau : le tableau doit-il contenir des objets ou des pointeurs vers ces objets ? Pourquoi ? Comparer à Java.*

Le type des éléments du tableau doit être un pointeur vers les objets. Si on stocke directement les objets dans le tableau, ils seront tronqués à la taille de la classe de base. Alors qu'en utilisant des pointeurs, on a accès aux méthodes spécifiques à la classe dérivée. En Java, les tableaux peuvent contenir des objets. En C++, on travaille sur la mémoire manuellement, donc on doit utiliser des pointeurs.

### Etape 7 
*Parmi les classes précédemment écrites quelles sont celles qu'il faut modifier afin qu'il n'y ait pas de fuite mémoire quand on détruit les objets ?*

Pour éviter les fuites de mémoire on doit modifier toutes les classes qui utilisent la mémoire dynamique, c'est-à-dire les classes qui créent des objets avec new. On doit donc modifier toutes les classes qui dérivent de MultimediaObject (soit Photo, Video, Film) et la classe Group.

*La copie d'objet peut également poser problème quand ils ont des variables d'instance qui sont des pointeurs. Quel est le problème et quelles sont les solutions ?*

Lorsque des objets avec des variables d’instance qui sont des pointeurs sont copiés, les pointeurs sont copiés, mais pas la mémoire vers laquelle ils pointent. Cela peut entraîner l’apparition de plusieurs objets pointant vers la même mémoire, ce qui peut entraîner une corruption de la mémoire. Pour éviter cela, le constructeur de copie et l’opérateur d’affectation doivent être modifiés pour allouer une nouvelle mémoire aux variables d’instance qui sont des pointeurs et copier les valeurs de l’objet d’origine vers la nouvelle mémoire. C’est ce qu’on appelle la copie profonde.

### Etape 8 
*Le groupe ne doit pas détruire les objets quand il est détruit car un objet peut appartenir à plusieurs groupes (on verra ce point à la question suivante). On rappelle aussi que la liste d'objets doit en fait être une liste de pointeurs d'objets. Pourquoi ? Comparer à Java.*

Dans le cas de la classe Group,les objets peuvent appartenir à plusieurs groupes. Si on stocke directement des objets dans la liste de groupes, on crée des copies des objets chaque fois qu'un objet est ajouté à un nouveau groupe. Cela peut entraîner des problèmes si on modifie l'objet dans un groupe, car les autres groupes contiendront toujours l'ancienne version de l'objet. On utilise donc des pointeurs d'objets. Chaque groupe contient un pointeur vers un objet et non une copie de l'objet lui-même.
En Java, les objets sont stockés sur le tas alors qu'ils sont sur le tas ou la pile en C++.

### Etape 10
*Les méthodes précédentes permettent d'assurer la cohérence de la base de données car quand on crée un objet on l'ajoute à la table adéquate. Par contre, ce ne sera pas le cas si on crée un objet directement avec new (il n'appartiendra à aucune table). Comment peut-on l'interdire, afin que seule la classe servant à manipuler les objets puisse en créer de nouveaux ?*

Pour empêcher la création directe d'objets avec new, on peut rendre le constructeur de la classe privé et créer une méthode statique publique pour créer de nouveaux objets.


## Questions Java
### Etape 1
*Lancez votre programme, cliquez plusieurs fois sur les deux premiers bouton, retaillez la fenêtre. Que constate-t'on ?*

On ne peut pas voir le texte qui dépasse du JTextArea, car il n'y a pas de scroll bar. Il faut donc ajouter un JScrollPane au JTextArea.