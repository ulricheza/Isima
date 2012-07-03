//
//  Ville.h
//  CommunesProjet
//
//  Created by Jean-Christophe SEPTIER on 2/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Ville : NSObject
{
    NSString  * name;
    NSString  * nameMAJ;
    int         codePostal;
    int         INSEE;
    int         codeRegion;
    float       latitude;
    float       longitude;
    float       eloignement;
}
@property (retain)  NSString  * name;
@property (retain)  NSString  * nameMAJ;  
@property int       INSEE;
@property int       codeRegion;
@property float     latitude;
@property float     longitude;
@property float     eloignement;
@property int       codepostal;


-(id)initWithString:(NSString*)aName;

+ (Ville *)createMyClassWithString: (NSString *) aName;


@end;
