#ifndef ARBREABSTRAIT_H
#define ARBREABSTRAIT_H

// Contient toutes les déclarations de classes nécessaires
//  pour représenter l'arbre abstrait

#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

#include "Symbole.h"
#include "Exceptions.h"

////////////////////////////////////////////////////////////////////////////////
class Noeud {
// Classe abstraite dont dériveront toutes les classes servant à représenter l'arbre abstrait
// Remarque : la classe ne contient aucun constructeur
  public:
    virtual int  executer() =0 ; // Méthode pure (non implémentée) qui rend la classe abstraite
    virtual void ajoute(Noeud* instruction) { throw OperationInterditeException(); }
    virtual ~Noeud() {} // Présence d'un destructeur virtuel conseillée dans les classes abstraites
};

////////////////////////////////////////////////////////////////////////////////
class NoeudSeqInst : public Noeud {
// Classe pour représenter un noeud "sequence d'instruction"
//  qui a autant de fils que d'instructions dans la séquence
  public:
     NoeudSeqInst();         // Construit une séquence d'instruction vide
    ~NoeudSeqInst() {}       // A cause du destructeur virtuel de la classe Noeud
    int executer() override; // Exécute chaque instruction de la séquence
    void ajoute(Noeud* instruction) override;  // Ajoute une instruction à la séquence

  private:
    vector<Noeud *> m_instructions; // pour stocker les instructions de la séquence
};

////////////////////////////////////////////////////////////////////////////////
class NoeudAffectation : public Noeud {
// Classe pour représenter un noeud "affectation"
//  composé de 2 fils : la variable et l'expression qu'on lui affecte
  public:
     NoeudAffectation(Noeud* variable, Noeud* expression); // construit une affectation
    ~NoeudAffectation() {}   // A cause du destructeur virtuel de la classe Noeud
    int executer() override; // Exécute (évalue) l'expression et affecte sa valeur à la variable

  private:
    Noeud* m_variable;
    Noeud* m_expression;
};

////////////////////////////////////////////////////////////////////////////////
class NoeudOperateurBinaire : public Noeud {
// Classe pour représenter un noeud "opération binaire" composé d'un opérateur
//  et de 2 fils : l'opérande gauche et l'opérande droit
  public:
    NoeudOperateurBinaire(Symbole operateur, Noeud* operandeGauche, Noeud* operandeDroit);
    // Construit une opération binaire : operandeGauche operateur OperandeDroit
   ~NoeudOperateurBinaire() {} // A cause du destructeur virtuel de la classe Noeud
    int executer() override;   // Exécute (évalue) l'opération binaire)

  private:
    Symbole m_operateur;
    Noeud*  m_operandeGauche;
    Noeud*  m_operandeDroit;
};

////////////////////////////////////////////////////////////////////////////////
class NoeudInstSi : public Noeud {
// Classe pour représenter un noeud "instruction si"
//  et ses 2 fils : la condition du si et la séquence d'instruction associée
  public:
    NoeudInstSi(Noeud* condition, Noeud* sequence);
     // Construit une "instruction si" avec sa condition et sa séquence d'instruction
   ~NoeudInstSi() {}         // A cause du destructeur virtuel de la classe Noeud
    int executer() override; // Exécute l'instruction si : si condition vraie on exécute la séquence

  private:
    Noeud*  m_condition;
    Noeud*  m_sequence;
};

////////////////////////////////////////////////////////////////////////////////
class NoeudInstTantQue : public Noeud {
// Classe pour représenter un noeud "instruction Tant que"
//  et ses 2 fils : la condition du si et la séquence d'instruction associée
  public:
    NoeudInstTantQue(Noeud* condition, Noeud* sequence);
     // Construit une "instruction tantque" avec sa condition et sa séquence d'instruction
   ~NoeudInstTantQue() {}         // A cause du destructeur virtuel de la classe Noeud
    int executer() override; // Exécute l'instruction tantque : si condition vraie on exécute la séquence

  private:
    Noeud*  m_condition;
    Noeud*  m_sequence;
};

////////////////////////////////////////////////////////////////////////////////

class NoeudInstPour : public Noeud {
// Classe pour représenter un noeud "instruction si"
//  et ses 2 fils : la condition du si et la séquence d'instruction associée
  public:
    NoeudInstPour(Noeud* condition, Noeud* sequence, Noeud* affectation1, Noeud* affectation2);
     // Construit une "instruction si" avec sa condition et sa séquence d'instruction
   ~NoeudInstPour() {}         // A cause du destructeur virtuel de la classe Noeudnew NoeudInstPour(condition, sequence);
    int executer() override; // Exécute l'instruction si : si condition vraie on exécute la séquence

  private:
    Noeud*  m_condition;
    Noeud*  m_sequence;
    Noeud*  m_affectation;
    Noeud*  m_incrementation;
};


class NoeudInstRepeter : public Noeud {
// Classe pour représenter un noeud "instruction Repeter"
    public:
        NoeudInstRepeter(Noeud* condition, Noeud* sequence);
     // Construit une "instruction Repeter" avec sa condition et sa séquence d'instruction

        ~NoeudInstRepeter() {}
        int executer() override; // Exécute l'instruction si : si condition vraie on exécute la séquence
    private:
        Noeud*  m_sequence;
        Noeud*  m_condition;
};

#endif /* ARBREABSTRAIT_H */
