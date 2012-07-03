//
//  MasterViewController.h
//  CommunesProjet
//
//  Created by Jean-Christophe SEPTIER on 2/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class DetailViewController;

@interface MasterViewController : UITableViewController
{
    NSMutableData   * dta;
    NSMutableArray         * myArrayVille;      
    
}

@property (strong, nonatomic) DetailViewController *detailViewController;
@property (nonatomic,retain) NSMutableData *dta;
@property (nonatomic, retain) NSArray *myArrayVille;

-(void)startdownload;

@end
