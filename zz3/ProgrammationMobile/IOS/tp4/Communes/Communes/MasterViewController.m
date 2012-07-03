//
//  MasterViewController.m
//  Communes
//
//  Created by Maxime Escourbiac on 07/02/12.
//  Copyright (c) 2012 ISIMA. All rights reserved.
//

#import "MasterViewController.h"

#import "DetailViewController.h"

@implementation MasterViewController

@synthesize detailViewController = _detailViewController;
@synthesize progressBar = _progressBar;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        self.title = NSLocalizedString(@"Communes", @"Communes");
        if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPad) {
            self.clearsSelectionOnViewWillAppear = NO;
            self.contentSizeForViewInPopover = CGSizeMake(320.0, 600.0);
        }
    }
    return self;
}
							
- (void)dealloc
{
    [_detailViewController release];
    [_progressBar release];
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
    
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone)
    {
        self.detailViewController = [[[DetailViewController alloc] initWithNibName:@"DetailViewController_iPhone" bundle:nil] autorelease];
    }
    else
    {
        self.detailViewController = [[[DetailViewController alloc] initWithNibName:@"DetailViewController_iPad" bundle:nil] autorelease];
    }
    
    //initialisation des elements graphiques de la progress 
    _progressBar.progress = 0.;
    
    
    //telechargement du fichier
    if(_data == nil){ 
		_data = [[NSMutableData alloc] init];
	}
    else{
        [_data setLength:0];
    }
    
	NSString *real_url = @"http://opium.openium.fr/iOs/tp4/ville-light.csv";
    
	_url = [NSURL URLWithString:real_url];
	_req = [NSURLRequest requestWithURL:_url];
	_connect = [NSURLConnection connectionWithRequest:_req delegate:self];
}

- (void)viewDidUnload
{
    [self setProgressBar:nil];
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

// Customize the number of sections in the table view.
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    int nb = 0;
    if( _tableauVille != NULL)
        nb = [_tableauVille count];
    
    return nb;
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

    // Configure the cell.
    if ( _tableauVille == NULL || [_tableauVille count] == 0)
    {
        cell.textLabel.text = @"Chargement";
    }
    else
    {
        cell.textLabel.text = [[_tableauVille objectAtIndex:indexPath.row] nom];
    }
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    Ville * temp = [_tableauVille objectAtIndex:indexPath.row];
    self.detailViewController.villeAffichage = temp;
    [self.navigationController pushViewController:self.detailViewController animated:YES];
}

//Methodes de gestion du telechargement
#pragma mark - Asynchronous connection
-(void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)inResponse {
    _tailleFichier = inResponse.expectedContentLength;
    [UIApplication sharedApplication].networkActivityIndicatorVisible = YES;
}

- (void)connection: (NSURLConnection *) connection didReceiveData:(NSData *)data {
    //get the response from data
    [_data appendData:data];
    _quantiteDonneesRecu += [data length];
    _progressBar.progress = _quantiteDonneesRecu / _tailleFichier;
}


 -(void)connectionDidFinishLoading:(NSURLConnection *)connection {
      
     _tableauVille = [[NSMutableArray alloc] init];
 
     NSMutableString  *result = [[NSMutableString alloc] initWithData:_data encoding:NSUTF8StringEncoding];
     NSArray * tableauData = [[NSArray alloc] initWithArray:[result componentsSeparatedByString:@"\n"]];
     NSArray * tableauLigne; 
     int i;
 
     for(i=1;i<[tableauData count];++i)
     {
         tableauLigne = [[NSArray alloc] initWithArray:[[tableauData objectAtIndex:i] componentsSeparatedByString:@";"]];
 
         if ([tableauLigne count] == 8 )
         {
             Ville * v    = [[Ville alloc] init];
             v.nom        = [tableauLigne objectAtIndex:0];
             v.nomMAJ     = [tableauLigne objectAtIndex:1];
             v.codePostal = [tableauLigne objectAtIndex:2];
             v.codeInsee  = [tableauLigne objectAtIndex:3];
             v.codeRegion = [tableauLigne objectAtIndex:4];
             v.latitude   = [[tableauLigne objectAtIndex:5] floatValue];
             v.longitude  = [[tableauLigne objectAtIndex:6] floatValue];
             v.distance   = [[tableauLigne objectAtIndex:7] floatValue];
 
             [_tableauVille addObject:v];
         }
     }
     
     [self.tableView performSelectorOnMainThread:@selector(reloadData) withObject:nil waitUntilDone:NO];
     [_data setLength:0];
     
     //Supression de la barre de chargement
     [_progressBar setHidden:true];
     [UIApplication sharedApplication].networkActivityIndicatorVisible = NO;
 }
 
@end
