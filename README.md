# Mini Compilateur Pascal

Ce dépôt contient le code source d'un mini-compilateur pour le langage Pascal. Il prend en entrée un fichier source écrit en Pascal et génère du code assembleur intermédiaire ainsi que son exécution.
Ce compilateur a été développé dans le cadre d'un projet académique pour illustrer les concepts fondamentaux de la compilation.

## Fonctionnalités
- Analyse lexicale, syntaxique et sémantique d'un programme Pascal
- Génération de code intermédiaire
- Interprétation du code intermédiaire généré
- Sauvegarde du code intermédiaire dans un fichier texte

## Utilisation
1. Cloner le dépôt sur votre machine locale :
   ```bash
      https://github.com/Mehdi-Elargoubi/Mini-Compilateur-Pascal.git
   ```

2. Compiler le code source :
      ```bash
          cd mini-compilateur-pascal
          gcc -o compilateur compilateur.c
      ```
3. Exécuter le compilateur avec un fichier source Pascal en tant qu'entrée :

      ```bash
      ./compilateur C:/Users/HP/Desktop/Mini-Compilateur-Pascal/test.p /*chemin_vers_fichier_source.p*/
      ```

4. Le code intermédiaire sera généré dans le fichier `pcode.txt`.

## Contributions

Les contributions sont les bienvenues ! Si vous souhaitez contribuer à ce projet, veuillez suivre les étapes suivantes :

1. Les contributions sont les bienvenues ! Si vous souhaitez contribuer à ce projet, veuillez suivre ces étapes :
2. Fork ce dépôt sur GitHub.
3. Créez une nouvelle branche pour vos modifications.
4. Faites vos modifications et testez-les localement.
5. Soumettez une demande de tirage avec une description détaillée de vos modifications.

## Auteurs

- [El Argoubi El Mehdi](https://github.com/Mehdi-Elargoubi)
- [Mohammed Yassine Boumehdi]
- [Abdelhakim Khaouiti]
- [Anass Bengmah]

## Licence

Ce projet est sous licence MIT - voir le fichier [LICENSE.md](LICENSE.md) pour plus de détails.
