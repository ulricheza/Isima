//
//  MasterDetailViewController.m
//  Master
//
//  Created by Maxime ESCOURBIAC on 1/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "MasterDetailViewController.h"

@interface MasterDetailViewController ()
@property (strong, nonatomic) UIPopoverController *masterPopoverController;
- (void)configureView;
@end

@implementation MasterDetailViewController

@synthesize detailText = _detailText;
@synthesize detailItem = _detailItem;
@synthesize detailDescriptionLabel = _detailDescriptionLabel;
@synthesize masterPopoverController = _masterPopoverController;
@synthesize dictionnaireDetail;

// Destruction du master
- (void)dealloc
{
    [_detailItem release];
    [_detailDescriptionLabel release];
    [_masterPopoverController release];
    [_detailText release];
    [dictionnaireDetail release];
    [super dealloc];
}

#pragma mark - Managing the detail item

// Donne l'id du détail
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
    // Update the user interface for the detail item.
    if (self.detailItem) {
        NSLog(@"id= %@", self.detailItem);
        
        if ([dictionnaireDetail objectForKey:self.detailItem] != nil) 
        {
            // Affiche les détails
          self.detailText.text =[dictionnaireDetail objectForKey:self.detailItem];
        } 
        else 
        {
            self.detailText.text = @"";
        }
    }else
    {
        self.detailText.text = @"";
    }
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
    [self setDetailText:nil];
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated
{
	[super viewWillDisappear:animated];
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

// Initialisation des détails
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        self.title = NSLocalizedString(@"Detail", @"Detail");
        [self initDictionnaireDetail];
    }
    return self;
}

// Initialise le dictionnaire
-(void)initDictionnaireDetail
{
    //On remplit les détails que l'on souhaite afficher
    dictionnaireDetail = [[NSMutableDictionary alloc] init];
    [dictionnaireDetail setObject:@"Alsace: Numéro 42" forKey:@"42"];
    [dictionnaireDetail setObject:@"Aquitaine: Numéro 72" forKey:@"72"];
    [dictionnaireDetail setObject:@"Auvergne: Numéro 83" forKey:@"83"];
    [dictionnaireDetail setObject:@"Bourgogne: Numéro 26" forKey:@"26"];
    [dictionnaireDetail setObject:@"Bretagne: Numéro 53" forKey:@"53"];
    [dictionnaireDetail setObject:@"Champagne-Ardenne: Numéro 24" forKey:@"24"];
    [dictionnaireDetail setObject:@"Corse: Numéro 21" forKey:@"21"];
    [dictionnaireDetail setObject:@"Franche-Comté: Numéro 43" forKey:@"43"];
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
