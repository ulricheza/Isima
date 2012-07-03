//
//  DetailViewController.m
//  Communes
//
//  Created by Maxime Escourbiac on 07/02/12.
//  Copyright (c) 2012 ISIMA. All rights reserved.
//

#import "DetailViewController.h"
#import "PointCarte.h"

@interface DetailViewController ()
@property (strong, nonatomic) UIPopoverController *masterPopoverController;
- (void)configureView;
@end

@implementation DetailViewController

@synthesize detailItem = _detailItem;
@synthesize mapView = _mapView;
@synthesize masterPopoverController = _masterPopoverController;
@synthesize villeAffichage = _villeAffichage;
@synthesize labelCodePostal = _labelCodePostal;
@synthesize labelNom = _labelNom;
@synthesize annotation = _annotation;

- (void)dealloc
{
    [_detailItem release];
    [_masterPopoverController release];
    [_mapView release];
    [_labelCodePostal release];
    [_labelNom release];
    [super dealloc];
}

#pragma mark - Managing the detail item

- (void)setDetailItem:(id)newDetailItem
{
    if (_detailItem != newDetailItem) {
        [_detailItem release]; 
        _detailItem = [newDetailItem retain]; 

        // Update the view.
        [self configureView];
    }

    if (self.masterPopoverController != nil) {
        [self.masterPopoverController dismissPopoverAnimated:YES];
    }
    
    
    
}

- (void)configureView
{

}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    [self configureView];
}

- (void)viewDidUnload
{
    [self setMapView:nil];
    [self setLabelCodePostal:nil];
    [self setLabelNom:nil];
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    //affichage de la ville
    NSMutableString *texteNom = [[[NSMutableString alloc] init] retain];
    NSMutableString *texteCodePostal = [[[NSMutableString alloc] init] retain];
    [texteNom appendString: @"Nom :"];
    [texteCodePostal appendString: @"Code Postal :"];
    
    if(_villeAffichage != nil)
    {
        [texteNom appendString: _villeAffichage.nom];
        [texteCodePostal appendString: _villeAffichage.codePostal];
    }
    
	// Affiche le texte dans notre label
    [_labelNom setText:texteNom];
    [_labelCodePostal setText:texteCodePostal];
    
    //GFestion de la carte
    //set the map center on the France
    CLLocationDegrees lat = (CLLocationDegrees)_villeAffichage.latitude;    
    CLLocationDegrees longi = (CLLocationDegrees)_villeAffichage.longitude;
    CLLocationCoordinate2D coordVille = { lat, longi };
    MKCoordinateRegion region = self.mapView.region;
    region.center = coordVille;
    region.span.longitudeDelta = 0.5;
    region.span.latitudeDelta = 0.5;
    [self.mapView setRegion:region animated:YES];
    _annotation = [[PointCarte alloc] initWithCoordinate:coordVille title:_villeAffichage.nom]; 
    [_mapView addAnnotation:_annotation];
    [_mapView selectAnnotation:_annotation animated:true];
    
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];

}

- (void)viewWillDisappear:(BOOL)animated
{
	[super viewWillDisappear:animated];
    [_mapView removeAnnotation:_annotation];
    [_annotation release];
}

- (void)viewDidDisappear:(BOOL)animated
{
	[super viewDidDisappear:animated];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
    } else {
        return YES;
    }
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        self.title = NSLocalizedString(@"Detail", @"Detail");
    }
    return self;
}
							
#pragma mark - Split view

- (void)splitViewController:(UISplitViewController *)splitController willHideViewController:(UIViewController *)viewController withBarButtonItem:(UIBarButtonItem *)barButtonItem forPopoverController:(UIPopoverController *)popoverController
{
    barButtonItem.title = NSLocalizedString(@"Master", @"Master");
    [self.navigationItem setLeftBarButtonItem:barButtonItem animated:YES];
    self.masterPopoverController = popoverController;
}

- (void)splitViewController:(UISplitViewController *)splitController willShowViewController:(UIViewController *)viewController invalidatingBarButtonItem:(UIBarButtonItem *)barButtonItem
{
    // Called when the view is shown again in the split view, invalidating the button and popover controller.
    [self.navigationItem setLeftBarButtonItem:nil animated:YES];
    self.masterPopoverController = nil;
}

@end
