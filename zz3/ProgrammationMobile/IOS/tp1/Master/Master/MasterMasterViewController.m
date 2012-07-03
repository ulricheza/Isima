//
//  MasterMasterViewController.m
//  Master
//
//  Created by Maxime ESCOURBIAC on 1/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "MasterMasterViewController.h"

#import "MasterDetailViewController.h"

@implementation MasterMasterViewController
@synthesize dictionnaireRegion;

@synthesize detailViewController = _detailViewController;

// Méthode d'initialisation du master
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        self.title = NSLocalizedString(@"Master", @"Master");
    }
	
    [self initDictionary];

    return self;
}

// Initialise le dictionnaire
-(void)initDictionary
{
    dictionnaireRegion = [[NSMutableDictionary alloc] init];
    [dictionnaireRegion setObject:@"Alsace" forKey:@"42"];
    [dictionnaireRegion setObject:@"Aquitaine" forKey:@"72"];
    [dictionnaireRegion setObject:@"Auvergne" forKey:@"83"];
    [dictionnaireRegion setObject:@"Bourgogne" forKey:@"26"];
    [dictionnaireRegion setObject:@"Bretagne" forKey:@"53"];
    [dictionnaireRegion setObject:@"Champagne-Ardenne" forKey:@"24"];
    [dictionnaireRegion setObject:@"Corse" forKey:@"21"];
    [dictionnaireRegion setObject:@"Franche-Comté" forKey:@"43"];
}

- (void)dealloc
{
    [dictionnaireRegion release];
    [_detailViewController release];
    [super dealloc];
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
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPad) {
        [self.tableView selectRowAtIndexPath:[NSIndexPath indexPathForRow:0 inSection:0] animated:NO scrollPosition:UITableViewScrollPositionMiddle];
    }
    
}

- (void)viewDidUnload
{
    [super viewDidUnload];
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

// Customize the number of sections in the table view.
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return 8;
}

// Customize the appearance of table view cells.
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CellIdentifier = @"Cell";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier] autorelease];
        if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
            cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
        }
    }
	// Affiche le nom de la région
    // Récupération des valeurs
    NSArray* allKeys = [dictionnaireRegion allKeys];
	cell.textLabel.text = [dictionnaireRegion objectForKey:[allKeys objectAtIndex:indexPath.row]];
    
    return cell;
}


// Méthode appelé quand on clique sur une cellule. Permet d'afficher la page de détail
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
	    if (!self.detailViewController) {
	        self.detailViewController = [[[MasterDetailViewController alloc] initWithNibName:@"MasterDetailViewController_iPhone" bundle:nil] autorelease];
	    }
        
        // Récupération des valeurs
        NSArray* allKeys = [dictionnaireRegion allKeys];
       
		// Changement du titre de la fenêtre
        self.detailViewController.title = [dictionnaireRegion objectForKey:[allKeys objectAtIndex:indexPath.row]];
		// Affichage des détails...
		[self.detailViewController setDetailItem:[allKeys objectAtIndex:indexPath.row]];
		// Lance la fenêtre
        [self.navigationController pushViewController:self.detailViewController animated:YES];
    }
}

@end
