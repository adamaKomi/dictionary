#pragma once
#include <iostream>
#include "File.h"
#include <string>
#include <algorithm>
#include <sstream>
#include <cctype>
#include <map>
#include <locale>
#include <cwctype>
#include <set>










using namespace std; 

// constructeur
File::File(std::string name)
	:fileName(name)
{
}

// fonction pour lire le fichier 
void File::readFile()
{
	ifstream MyFile(fileName);

    // si l'ouverture echoue
	if (!MyFile.is_open())
	{
		cerr << "Erreur : Impossible d'ouvrir le fichier " << fileName << endl;
		return;
	}


	string line;// pour lire les lignes
	string mot;

    // lire chaque ligne et extraire les mots
	while (getline(MyFile, line))
	{
		// Lire mot par mot
		std::istringstream flux(line);
       
		while (flux >> mot)
		{
            mot = cleanWord(mot);
            if (mot.length() != 0)
			    mots.push_back(cleanWord(mot));
		}
	}
    // fermer le fichier
	MyFile.close();
}


// fonction pour trier les mots par ordre alphabetique
void File::sortFile()
{
	sort(begin(mots), end(mots));
}





// fonction pour nettoyer les mots des ponctuations
std::string File::cleanWord(const std::string& word) const
{
	// Trouver la première occurrence d'un caractère de ponctuation
	size_t pos = 0;
	while (pos < word.size() && !ispunct(static_cast<unsigned char>(word[pos])) ){
		++pos;
	}

	// Retourner la sous-chaîne jusqu'à ce point
	return word.substr(0, pos);
}




// fonction pour chercher les mots les plus frequents
void File::mostUsedWords(int nbr)
{
	std::map<std::string, int> tab;

	for (std::string w : this->mots)
	{
		if(w!="")
			tab[w]++;
	}

	std::vector<std::pair<std::string, int>> sortedWords(tab.begin(), tab.end());


	std::sort(sortedWords.begin(), sortedWords.end(),
		[](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
			return b.second < a.second; // Tri décroissant
		});


	int i = 0;
    // afficher les mots
	for (const auto& word : sortedWords)
	{
		cout << word.first << " / " << word.second << endl;
		if(++i == nbr ) break;
	}
}



// fonction pour chercher un mot
int File::findWord(std::string mot)
{
    //conmpteur du nombre d'occurence du mot
	int cpt = 0;


	mot = cleanWord(mot);// nettoyer le mot des ponctuations
	for (int i = 0; i< mots.size(); i++)
	{
		if ( mots[i] == mot)
		{
			cpt++;
		}
	}

	if (cpt != 0)// le mot est trouvé
	{
		cout << "Mot \""<<mot<<"\" trouvé avec " << cpt<< " occurences" << endl;
	}
	else// le mot n'est pas trouvé
		cout << "Mot non trouve" << endl;

	return cpt;
}




// fonction pour remplacer un mot par un autre
void File::replaceWord(std::string mot, std::string replaceBy, int nbTimes)
{

	int cpt = 0;// le nombre de fois que le mot mot doit etre remplacé
	for (int i = 0; i < mots.size(); i++)
	{
		if (mots[i] == mot)
		{
			if (cpt++ == nbTimes) break;
			mots[i] = replaceBy;
		}
	}

    std::cout <<"\"" << replaceBy << "\" remplace " << nbTimes << " fois le mot \""<< mot << "\"" << std::endl;
    return;
}




// fonction pour transformer le texte en majiscule
void File::textToUpper()
{
    for(int i = 0; i<mots.size(); i++)
    { 
        // Conversion en majuscules
        std::transform(mots[i].begin(), mots[i].end(), mots[i].begin(), ::toupper);
    }
    std::cout << "Transformation terminee" << std::endl;
}



// fonction pour transformer le texte en miniscule
void File::textToLower()
{
    for (int i = 0; i < mots.size(); i++)
    {
        // Conversion en majuscules
        std::transform(mots[i].begin(), mots[i].end(), mots[i].begin(), ::tolower);
        std::cout << "Transformation terminee" << std::endl;
    }
}




// fonction pour ajouter un mot
void File::addWord(std::string word)
{

    std::string mot;
    std::istringstream flux(word);
    int cpt = 0;

    // si le parametre est composé de plusieurs mots, on ajoute chaque mot
    while (flux >> mot)
    {
        mots.push_back(cleanWord(mot));
        cpt++;
    }

    if (cpt != 0)
    {
        std::cout << "Ajouter avec succes" << std::endl;
    }
    else
        std::cout << "Ajout non pris en compte" << std::endl;
    return;
}





// fonction pour afficher le texte
void File::printFile() const
{
	for (const auto& x : mots)
	{
		cout << x << endl;
	}
}





// fonction pour tester les autres fonctions
void File::browseDictionary() const
{
    File f = *this;
    f.readFile();

    std::string oldWord, newWord, mot;

    int choix, nbTotal, nbReplace, choice, nbr;

    // le menu
    std::string menu = "\n1-Afficher le texte";
    menu += "\n2-Afficher le texte par ordre Alphabétique";
    menu += "\n3-Rechercher un mot\n4-Remplacer un mot";
    menu += "\n5-Afficher les mots les plus utilisés ";
    menu += "\n6-Transformer le texte en majiscule ";
    menu += "\n7-Transformer le texte en miniscule ";
    menu += "\n8-Ajouter un mot ";
    menu += "\n0 - Quitter";

    std::string menuReplace = "\n1-Une occurence\n2-Toutes les occurences\n3-Un nombre precis\n0-Annuler";
    

    do
    {
        std::cout << menu << std::endl;
        std::cout << ">>>";
        std::cin >> choix;
        std::cout << std::endl;

        switch (choix)
        {
        case 1:// afficher le texte
            f.printFile();
            break;
        case 2:// afficher le texte trié
            f.sortFile();
            f.printFile();
            break;
        case 3:// rechercher un mot
            std::cout << "Rechercher un mot : ";

            std::cin >> mot;
            f.findWord(mot);
            break;
        case 4:// remplacer un mot par un autre

            std::cout << "Mot a remplacer :" << std::endl;
            std::cout << ">>>";
            std::cin >> oldWord;
            std::cout << std::endl;

            if ((nbTotal = f.findWord(oldWord)) == 0)
            {
                std::cout << ">> Impossible de faire le remplacement" << std::endl;
                break;
            }

            std::cout << std::endl;
            std::cout << "Nouveau mot :" << std::endl;
            std::cout << ">>>";
            std::cin >> newWord;
            std::cout << std::endl;


            std::cout << "Options de remplacement :" << std::endl;
            std::cout << menuReplace << std::endl;
            std::cout << ">>>";
            std::cin >> choice;
            std::cout << std::endl;

            switch (choice)
            {
            case 1:
                f.replaceWord(oldWord, newWord, 1);
                break;
            case 2:
                f.replaceWord(oldWord, newWord, nbTotal);
                break;
            case 3:
                std::cout << "Entrer un nombre (max = " << nbTotal << ")" << std::endl;
                std::cout << ">>>";
                std::cin >> nbReplace;
                std::cout << std::endl;
                if (nbReplace > nbTotal)
                {
                    std::cout << "Impossible de remplacer, le nombre max de remplacement : " << nbTotal << std::endl;
                    break;
                }
                f.replaceWord(oldWord, newWord, nbReplace);
                break;
            default:
                break;
            }

            break;
        case 5:// afficher les mots les plus frequents
      
            std::cout << "Entrer le nombre de mot a afficher :" << std::endl;
            std::cout << ">>>";
            std::cin >> nbr;
            std::cout << std::endl;
            if (nbr <= 0) break;
            std::cout <<nbr<< " mots les plus frequents : " << std::endl;
            f.mostUsedWords(nbr);
            break;
        case 6: // rendre le texte majiscule
            f.textToUpper();
            break;
        case 7: // rendre le texte miniscule
            f.textToLower();
            break;
        case 8: // ajouter un mot 
            std::cout << "Entrer un mot a ajouter" << std::endl;
            std::cout << ">>>";
            std::cin >> mot;
            std::cout << std::endl;
            f.addWord(mot);
            break;
        case 0:
            break;

        }
    } while (choix != 0);
}
