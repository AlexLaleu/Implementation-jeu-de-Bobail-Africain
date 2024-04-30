Ce projet consiste à implémenter le jeu traditionnel africain Bobail en langage C. 
Le jeu sera jouable en utilisant le fichier bobail.c, et toutes les fonctions intermédiaires seront codées dans d'autres fichiers pour une meilleure organisation du code.
Le jeu se joue avec un seul joueur contre la machine. L'ensemble du jeu se déroule dans le terminal de l'utilisateur.
On va représenter les pions verts par les nombres de 1 à 5 sur le plateau, les pions rouges entre 6 et 10, le pion jaune (BOBAIL) par -1 et les cases vides par 0.
On utilise la configuration initiale du site https://boulder-nautilus-254.notion.site/Sujet-515cc36d34f54bbdbf2279ea5b0e4c0b (pions verts en haut, pions rouges en bas).
L'utilisateur va jouer les pions verts, la machine les pions rouges.


Compilation et exécution :
L'éxécution du jeu est automatisée avec le makefile et le jeu s'affiche directement dans votre terminal grâce à la commande "make run".

Suppression de l'éxécutable et des fichiers objets :
N'oubliez pas de supprimer les fichiers crées pour l'éxécution grâce à la commande "make clean".
