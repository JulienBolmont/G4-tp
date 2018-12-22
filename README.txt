Compilation.
------------

Le code source se trouve dans le répertoire "TP".
1. Créer un répertoire "TP-build" au même niveau que le répertoire TP :
    mkdir TP-build
    cd TP-build
2. Une fois dans le répertoire TP-build, configurer le projet avec cmake :
    cmake -DGeant4_DIR=$G4BASELIBDIR ../TP
   Avec l'option debug :
    cmake -DGeant4_DIR=$G4BASELIBDIR -DCMAKE_BUILD_TYPE=Debug ../TP
3. Lancer la compilation :
    make

L'étape 2 copie tous les fichiers utiles dans le répertoire TP-build.
