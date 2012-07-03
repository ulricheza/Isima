//
//  Ville.m
//  Communes
//
//  Created by Maxime Escourbiac on 07/02/12.
//  Copyright (c) 2012 ISIMA. All rights reserved.
//

#import "Ville.h"



@implementation Ville

@synthesize nom         = _nom;
@synthesize nomMAJ      = _nomMAJ;
@synthesize codePostal  = _codePostal;
@synthesize codeInsee   = _codeInsee;
@synthesize codeRegion  = _codeRegion;
@synthesize distance    = _distance;
@synthesize latitude    = _latitude;
@synthesize longitude   = _longitude;


- (void)dealloc {
    [_nom release];
    [_nomMAJ release];
    [_codePostal release];
    [_codeInsee release];
    [_codeRegion release];
}
@end
