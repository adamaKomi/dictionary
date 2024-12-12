#pragma once
#include <iostream>
#include <fstream> 
#include <vector>

class File
{
private:
	std::string fileName; // nom du fichier
	std::vector<std::string> mots{};// liste des mots
public:
	File(std::string name);
	void readFile();// lire le fichier
	void sortFile();// trier le texte

	// nettoyer un mot de ses ponctuation
	std::string cleanWord(const std::string& word) const;

	// afficher les mots les plus utilisés
	void mostUsedWords(int nbr);

	// rechercher un mot
	int findWord(std::string mot);

	// remplacer un mot par un autre
	void replaceWord(std::string mot, std::string replaceBy, int nbTimes);
	// rendre le texte majiscule
	void textToUpper();
	// rendre le texte miniscule
	void textToLower();
	// ajouter un mot 
	void addWord(std::string word);
	// afficher le texte
	void printFile()const;
	// tester les fonctions
	void browseDictionary() const;
};



