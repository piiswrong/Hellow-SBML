#include <QtCore/QCoreApplication>
#include <sbml/SBMLTypes.h>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    char buff[100] = "./";
    strcat( buff,  a.argv()[1] );
    SBMLDocument* sbmlDoc = readSBML( buff );
    FILE* fout = fopen("out.out" , "w");
    Model* sbmlMod = sbmlDoc->getModel();


    Compartment * com = sbmlMod->getCompartment(0);
    fprintf(fout , "Compartmants:\n");
    for( int i = 1 ; com ; com = sbmlMod->getCompartment(i) , i++ )
    {
        fprintf(fout , "%s\n" , com->getId().c_str() );
    }
    fprintf(fout,"\n");

    Species * Spe = sbmlMod->getSpecies(0);
    fprintf(fout , "Species:\n");
    for( int i = 1 ; Spe ; Spe = sbmlMod->getSpecies(i) , i++ )
    {
        fprintf(fout , "%s\n" , Spe->getId().c_str() );
    }
    fprintf(fout , "\n" );

    Parameter * Par = sbmlMod->getParameter(0);
    fprintf(fout , "Parameters:\n");
    for( int i = 1 ; Par ; Par = sbmlMod->getParameter(i) , i++ )
    {
        fprintf(fout , "%s=%d\n" , Par->getId().c_str() , (int)Par->getValue() );
    }
    fprintf(fout , "\n");

    Reaction * Rea = sbmlMod->getReaction(0);
    fprintf(fout , "Reactions:\n");
    for( int i = 1 ; Rea ; Rea = sbmlMod->getReaction(i) , i++ )
    {
        fprintf(fout , "%s: " , Rea->getId().c_str() );
        SpeciesReference * Sref = Rea->getReactant(0);
        if( Sref ) fprintf(fout , "%s" , Sref->getSpecies().c_str() );
        Sref = Rea->getReactant(1);
        for( int j = 2 ; Sref ; Sref = Rea->getReactant(j) , j++  )
        {
            fprintf(fout , "+%s" , Sref->getSpecies().c_str() );
        }
        fprintf(fout , "->" );

        Sref = Rea->getProduct(0);
        if( Sref ) fprintf(fout , "%s" , Sref->getSpecies().c_str() );
        Sref = Rea->getProduct(1);
        for( int j = 2 ; Sref ; Sref = Rea->getProduct(j) , j++  )
        {
            fprintf(fout , "+%s" , Sref->getSpecies().c_str() );
        }
        fprintf(fout , "\n");
    }
    fprintf(fout , "\n" );

    fclose(fout);
    exit(0);
    return a.exec();
}
