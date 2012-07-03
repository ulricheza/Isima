//
//  MasterViewController.m
//  CommunesProjet
//
//  Created by Jean-Christophe SEPTIER on 2/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "MasterViewController.h"
#import "Ville.h"
#import "DetailViewController.h"

@implementation MasterViewController

@synthesize detailViewController = _detailViewController;
@synthesize dta;
@synthesize myArrayVille;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        self.title = NSLocalizedString(@"Master", @"Master");
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
    
    [self startdownload];
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
    if ([myArrayVille count] == 0)
        return 1;
    else
        return [myArrayVille count];
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
    if ([myArrayVille count] == 0)
        cell.textLabel.text = @"Chargement";
    else
        cell.textLabel.text = [[myArrayVille objectAtIndex:indexPath.row] name];
    return cell;
}

/*
// Override to support conditional editing of the table view.
- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Return NO if you do not want the specified item to be editable.
    return YES;
}
*/

/*
// Override to support editing the table view.
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        // Delete the row from the data source.
        [tableView deleteRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:UITableViewRowAnimationFade];
    } else if (editingStyle == UITableViewCellEditingStyleInsert) {
        // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view.
    }   
}
*/

/*
// Override to support rearranging the table view.
- (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)fromIndexPath toIndexPath:(NSIndexPath *)toIndexPath
{
}
*/

/*
// Override to support conditional rearranging of the table view.
- (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Return NO if you do not want the item to be re-orderable.
    return YES;
}
*/

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{  
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
	    if (!self.detailViewController) {
	        self.detailViewController = [[[DetailViewController alloc] initWithNibName:@"DetailViewController_iPhone" bundle:nil] autorelease];
	    }
        [self.navigationController pushViewController:self.detailViewController animated:YES];
    }
}

-(void)startdownload { // appelez cette méthode pour lancer le téléchargement
    
	if(dta == nil){ 
		dta = [[NSMutableData alloc] init];
	}
    else{
        [dta setLength:0];
    }
    
	NSString *real_url = @"http://opium.openium.fr/iOs/tp4/ville-light.csv";

	NSURL           *url = [NSURL URLWithString:real_url];
	NSURLRequest    *req = [NSURLRequest requestWithURL:url];
	NSURLConnection *connect = [NSURLConnection connectionWithRequest:req delegate:self];
    
}

-(void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data {
	[dta appendData:data];
}

-(void)connectionDidFinishLoading:(NSURLConnection *)connection {

    myArrayVille = [[NSMutableArray alloc] init];
    
	NSMutableString *result = [[NSMutableString alloc] initWithData:dta encoding:NSUTF8StringEncoding];
       
    NSArray *arrayLigne = [[NSArray alloc] initWithArray:[result componentsSeparatedByString:@"\n"]];
    NSArray *arrayVille;
 
  
    int i , j;
    NSString * ligne;
    NSString * stringVille;
    NSString * stringVilleMAJ;
    int         INSEE;
    int         codeRegion;
    int         codepostal;
    float       latitude;
    float       longitude;
    float       eloignement;

    for(i=1;i<[arrayLigne count];i++)
    {
        ligne = [arrayLigne objectAtIndex:i];
        arrayVille = [[NSArray alloc] initWithArray:[ligne componentsSeparatedByString:@";"]];
        
        if ([arrayVille count] == 8 )
        {
            stringVille     = [arrayVille objectAtIndex:0];
            stringVilleMAJ  = [arrayVille objectAtIndex:1];
            codepostal      = [[arrayVille objectAtIndex:2] intValue];
            INSEE           = [[arrayVille objectAtIndex:3] intValue];
            codeRegion      = [[arrayVille objectAtIndex:4] intValue];
            latitude        = [[arrayVille objectAtIndex:5] floatValue];
            longitude       = [[arrayVille objectAtIndex:6] floatValue];
            eloignement     = [[arrayVille objectAtIndex:7] floatValue];
        
        
            Ville * v = [[Ville alloc] init];
            v.name    = stringVille;
            v.nameMAJ = stringVilleMAJ;
            v.INSEE = INSEE;
            v.codeRegion = codeRegion;
            v.latitude = latitude;
            v.longitude = longitude;
            v.eloignement = eloignement;
                
            [myArrayVille addObject:v];
        }
    }
   	 [self.tableView performSelectorOnMainThread:@selector(reloadData) withObject:nil waitUntilDone:NO];
    
    [dta setLength:0];
}



/*
-(void)loadQuiz
{
	NSBundle *bundle = [NSBundle mainBundle];
	NSString *textFilePath = [bundle pathForResource:@"quizgame" ofType:@"txt"];
	NSString *fileContents = [NSString stringWithContentsOfFile:textFilePath];
	NSArray *quizArray = [[NSArray alloc] initWithArray:[fileContents componentsSeparatedByString:@"\n"]];
	self.theQuiz = quizArray;
	[quizArray release];
}
*/
@end
