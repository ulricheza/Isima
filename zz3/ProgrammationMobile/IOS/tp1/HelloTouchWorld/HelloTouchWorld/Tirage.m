//
//  Tirage.m
//  HelloTouchWorld
//
//  Created by Maxime ESCOURBIAC on 1/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "Tirage.h"


@implementation Tirage

// Initialise le générateur
-(id)init
{
    self = [super init];
    srand(time(nil));
    return self;
}

// Génère un int entre 0 et 100
-(int) generateInt 
{
    return (int)rand()%51;
}

// Génère le numéro complémentaire
-(int) generateIntComp 
{
    return (int)rand()%11;
}

@end
