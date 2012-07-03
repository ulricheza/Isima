//
//  Tirage.h
//  HelloTouchWorld
//
//  Created by Maxime ESCOURBIAC on 1/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <stdlib.h>
#import <time.h>

// Classe Tirage qui permet de tirer des objets
@interface Tirage : NSObject
{
}
-(id)init;
-(int) generateInt;
-(int) generateIntComp;
@end
