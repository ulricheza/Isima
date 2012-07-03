//
//  HelloWorldViewController.h
//  HelloTouchWorld
//
//  Created by Maxime ESCOURBIAC on 1/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "Tirage.h"

@interface HelloWorldViewController : UIViewController
{
    Tirage * tirage; // Classe permettant de tirer des numéros
    
}
@property (retain, nonatomic) IBOutlet UILabel *labelText; // Label ou afficher le tirage

@property (retain, nonatomic) IBOutlet UIButton *buttonTirage; // Bouton pour tirer
- (IBAction)clickTirage:(id)sender;

@end
