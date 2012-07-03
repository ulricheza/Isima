//
//  MasterViewController.h
//  Communes
//
//  Created by Maxime Escourbiac on 07/02/12.
//  Copyright (c) 2012 ISIMA. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "Ville.h"

@class DetailViewController;

@interface MasterViewController : UITableViewController
{
    NSMutableData   * _data;
    NSMutableArray  * _tableauVille;
    NSURL           * _url;
	NSURLRequest    * _req;
	NSURLConnection * _connect;
    float             _tailleFichier;
    float             _quantiteDonneesRecu;
}

@property (strong, nonatomic) DetailViewController *detailViewController;

@property (retain, nonatomic) IBOutlet UIProgressView *progressBar;

@end
