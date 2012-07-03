/**
 * \file main.cpp
 * \brief fichier main du tp2
 * \author Maxime Escourbiac Jean-Christophe Septier
 * \version 1.0
 * \date Lundi 25 Octobre 2010
 */

#include "main.h"

#define TAILLE_POP 40
#define NBRE_ITER 50
#define ITER_MAX 500
#define CHOIX_ALGO 0

int main(int argc, char** argv) {

  chromosome * result;
  instance * inst = new instance("instance.txt");
  srand(time(0));
  if(CHOIX_ALGO == 0){
     printf("algo memetique\n");
     for(int i = 0;i<30;++i){
       result = algo_memetique(inst);
       printf("makespan : %f \n",result->makespan);
       }
  }
  else{
       printf("algo genetique\n");
       for(int i = 0;i<30;++i){
       result = algo_memetique(inst);
       printf("makespan : %f \n",result->makespan);
       }
  }
  return 0;
}


chromosome * algo_memetique(instance * inst)
{
  register int i,j;
  int indiceC1,indiceC2,iter = 0;
  int * vect,*f1,*f2, *temp_mutation;
  float makespan1,makespan2;
  chromosome * temp;
  
  list<chromosome*> population;
  list<chromosome*>::iterator li1,li2;
  //initialisation de la population
  while(population.size()<TAILLE_POP)
  {
	 temp = new chromosome();
     vect = inst->gene_vecteur_alea();
     inst->recherche_locale(vect,NBRE_ITER);
	 temp->vect = vect;
	 temp->makespan = inst->getMakespan();
	 population.push_back(temp);
     inst->supArc();
	 population.sort(compare_distance);
	 population.unique(compare_makespan);
  }
  
  //phase d'ameliaration iterative
  while(iter < ITER_MAX )
  {
     population.sort(compare_distance);
     //choix des chromosomes
     indiceC1 = rand()%(TAILLE_POP/3);
     indiceC2 = rand()%(TAILLE_POP/2);
     li1 = population.begin();
     li2 = li1;
     for(i=0;i<indiceC1;++i)
        ++li1;
     for(i=0;i<indiceC2;++i)
        ++li2;
     inst->croisementLOX((*li1)->vect, (*li2)->vect, &f1, &f2);
     
     
     //pour le fils1
     inst->recherche_locale(f1,NBRE_ITER);
     makespan1 = inst->getMakespan();
     inst->supArc();
     temp_mutation = inst->mutation(f1);
     inst->ajoutArcsVecteur(temp_mutation);
     inst->bellman();
     inst->supArc();
     if(makespan1 < inst->getMakespan())
     {
        delete[] temp_mutation;
     }
     else
     {
        delete[] f1;
        f1 = temp_mutation;
        makespan1 = inst->getMakespan();
     }
     
     if(makespan1 < population.back()->makespan)
     {
		temp->vect = f1;
        temp->makespan = makespan1;
        population.push_back(temp);
        population.sort(compare_distance);
        population.unique(compare_makespan);
		if(population.size()>TAILLE_POP)
		{
		   delete[] population.back()->vect;
           delete   population.back();
		   population.pop_back();
		}
        temp = new chromosome();
        
     }
     else
     {
        delete[] f1;
     }
     
     //pour le fils2
     inst->recherche_locale(f2,NBRE_ITER);
     makespan2 = inst->getMakespan();
     inst->supArc();
     temp_mutation = inst->mutation(f2);
     inst->ajoutArcsVecteur(temp_mutation);
     inst->bellman();
     inst->supArc();
     if(makespan2 < inst->getMakespan())
     {
        delete[] temp_mutation;
     }
     else
     {
        delete[] f2;
        f2 = temp_mutation;
        makespan2 = inst->getMakespan();
     }
     if(makespan2 < population.back()->makespan)
     {
		temp = new chromosome();
        temp->vect = f2;
        temp->makespan = makespan2;
        population.push_back(temp);
		population.sort(compare_distance);
        population.unique(compare_makespan);
		if(population.size()>TAILLE_POP)
		{
           delete[] population.back()->vect;
           delete   population.back();
           population.pop_back();
		} 
     }
     else
     {
        delete[] f2;
     }     
     
     ++iter;
  }
  temp = population.front();
  while(population.size()>1)
  {
	  delete[] population.back()->vect;
	  delete population.back();
	  population.pop_back();
  }
  population.pop_back();
  return temp;
}

chromosome * algo_genetique(instance * inst)
{
	int i,j,iter, indiceC1,indiceC2;
	chromosome * temp;
	int * vect,*f1,*f2, *f1Mut, *f2Mut;
	int nbFils;
	//initialisation de la population
	list<chromosome*> population, populationFils;
	list<chromosome*>::iterator li,li1,li2;
	float makespan1,makespan2;
	bool test;
	for(i=0;i<TAILLE_POP;++i)
	{
		temp = new chromosome(); 
		do
		{
			vect = inst->gene_vecteur_alea();
			inst->ajoutArcsVecteur(vect);
			inst->bellman();
			inst->supArc();
			test=true;
			li=population.begin();
			while(li!=population.end() && test==true)
			{
				if((*li)->makespan==inst->getMakespan())
					test=false;
				++li;
			}
		}	
		while(test==false);
		temp->makespan=inst->getMakespan();
		temp->vect=vect;
		population.push_back(temp);
		
	}
       population.sort(compare_distance);

    //phase d'ameliaration iterative
	for(iter=0; iter < ITER_MAX ; iter++)
	{
		populationFils.clear();
		nbFils=0;
		while(nbFils<TAILLE_POP)
		{
			     //choix des chromosomes
			indiceC1 = rand()%(TAILLE_POP/3);
			indiceC2 = rand()%TAILLE_POP;

			li1 = population.begin();
			li2 = li1;
				
			for(i=0;i<indiceC1;++i)
				li1++;
			for(i=0;i<indiceC2;++i)
				li2++;
					
			inst->croisementLOX((*li1)->vect, (*li2)->vect, &f1, &f2);
				
			// Traitement du fils 1
			inst->ajoutArcsVecteur(f1);
			inst->bellman();
			makespan1 = inst->getMakespan();
			inst->supArc();

				
			//Mutation du fils1
			f1Mut = inst->mutation(f1);
			inst->ajoutArcsVecteur(f1Mut);
			inst->bellman();
			inst->supArc();
				
			if(makespan1 < inst->getMakespan())
				delete[] f1Mut;
			else
			{
				delete[] f1;
				f1 = f1Mut;
				makespan1 = inst->getMakespan();
			}
				
			// Insertion du fils 1 dans la population fils
			temp = new chromosome();
			temp->vect = f1;
			temp->makespan = makespan1;
			populationFils.push_back(temp);
			nbFils++;
			// Traitement du fils 2
			inst->ajoutArcsVecteur(f2);
			inst->bellman();
			makespan2 = inst->getMakespan();
			inst->supArc();

			//Mutation du fils2
			f2Mut = inst->mutation(f2);
			inst->ajoutArcsVecteur(f2Mut);
			inst->bellman();
			inst->supArc();
					
			if(makespan2 < inst->getMakespan())
			   delete[] f2Mut;
			else
			{
				delete[] f2;
				f2 = f2Mut;
				makespan2 = inst->getMakespan();
			}
						
			// Insertion du fils 1 dans la population fils
			temp = new chromosome();
			temp->vect = f2;
			temp->makespan = makespan2;
			populationFils.push_back(temp);
			nbFils++;				
		}

		populationFils.sort(compare_distance);
		population.merge(populationFils,compare_distance);
		population.unique(compare_makespan);
		while(population.size()<TAILLE_POP)
			population.pop_back();

	}
	
	return population.front();
}

bool compare_distance(chromosome * first, chromosome * second)
{
  return(first->makespan < second->makespan);
}   

bool compare_makespan(chromosome * first, chromosome * second)
{
  return(first->makespan == second->makespan);
}