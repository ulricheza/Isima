//
//  DetailViewController.h
//  Communes
//
//  Created by Maxime Escourbiac on 07/02/12.
//  Copyright (c) 2012 ISIMA. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MapKIt/Mapkit.h>
#import "Ville.h"
#import "PointCarte.h"

@interface DetailViewController : UIViewController <UISplitViewControllerDelegate>

@property (strong, nonatomic) id detailItem;

@property (retain, nonatomic) IBOutlet MKMapView * mapView;
@property (strong) Ville * villeAffichage;
@property (strong) PointCarte * annotation;
@property (retain, nonatomic) IBOutlet UILabel *labelCodePostal;
@property (retain, nonatomic) IBOutlet UILabel *labelNom;

@end
