# DiCtionary
*Project C semestre 3 - EFREI PARIS*

## Description
Dictionary is a program that allows you to search for a word in a dictionary and to add a word to the dictionary.
You can also generate sentences from words in the dictionary.

## How to use
### Search a word
To search a word, you have to type the word you want to search in the terminal.
You can ask for auto-completion by typing tab.
If the word is in the dictionary, you will see the word and its alternatives forms.

You can use 2 algorithms to search a word in the dictionary:
- A search with base form of the word, faster.
- A search with all the forms of the word, slower.

You can also precise the type of your word to accelerate the search.

### Add a word
To add a word, you have to type the word you want to add in the terminal.
You will be asked to enter the word's base form, the word's type and its associated tags.

### Generate sentences
You have 3 differents models of sentences you can generate:
- noun adj verb det noun
- noun 'qui' verb verb noun adj
- pronoun verb determinant noun past participe "que" subjonctif determinant noun
  
You can also choose your intensity of randomness:
- A dumb random, where the algorithm navigate into the tree randomly.
- A smart random, where the algorithm navigate into the tree with a probability based on the number of words in the tree.

## Credits
In this project, we used the following libraries:
- [uthash](https://troydhanson.github.io/uthash/)

## Authors
- Paul Mairesse
- Axel Loones
- Quentin Cardona
