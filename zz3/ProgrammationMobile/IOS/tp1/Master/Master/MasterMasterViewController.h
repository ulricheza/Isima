//
//  MasterMasterViewController.h
//  Master
//
//  Created by Maxime ESCOURBIAC on 1/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class MasterDetailViewController;

@interface MasterMasterViewController : UITableViewController
{
    NSMutableDictionary *dictionnaireRegion;
}

-(void)initDictionary;

@property (retain,nonatomic) NSMutableDictionary *dictionnaireRegion;
@property (strong, nonatomic) MasterDetailViewController *detailViewController;

@end
