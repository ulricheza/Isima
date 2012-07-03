//
//  MasterDetailViewController.h
//  Master
//
//  Created by Maxime ESCOURBIAC on 1/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface MasterDetailViewController : UIViewController <UISplitViewControllerDelegate>
{
    NSMutableDictionary *dictionnaireDetail;
}

-(void)initDictionnaireDetail;

@property (retain, nonatomic) IBOutlet UILabel *detailText; // Label ou afficher les détails

@property (strong, nonatomic) id detailItem; // Id du détail

@property (retain, nonatomic) NSMutableDictionary *dictionnaireDetail; // Dictionnaire de détails

@property (strong, nonatomic) IBOutlet UILabel *detailDescriptionLabel; 

@end
