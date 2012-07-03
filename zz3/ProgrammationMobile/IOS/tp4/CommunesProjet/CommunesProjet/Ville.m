//
//  Ville.m
//  CommunesProjet
//
//  Created by Jean-Christophe SEPTIER on 2/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "Ville.h"

@implementation Ville
@synthesize name;
@synthesize INSEE;
@synthesize nameMAJ;
@synthesize codeRegion;
@synthesize latitude;
@synthesize longitude;
@synthesize eloignement;
@synthesize codepostal;

-(id)initWithName:(NSString*) aName
{
    self = [super init];
    name = aName;
    return self;
}

+ (Ville *)createMyClassWithString: (NSString *) aName
{
    return [[[self alloc] initWithString:aName] autorelease];
}


@end
