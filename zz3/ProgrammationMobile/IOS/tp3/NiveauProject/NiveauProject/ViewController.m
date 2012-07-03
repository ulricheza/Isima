//
//  ViewController.m
//  NiveauProject
//
//  Created by Jean-Christophe SEPTIER on 1/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "ViewController.h"



@implementation ViewController
@synthesize labelXYZ;
@synthesize niveauBar;
@synthesize bulle;
@synthesize bulle;
@synthesize niveauBar;

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    [self configureAccelerometer];
    xprec = 0.;
    yprec = 0.;
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)viewDidUnload
{
    [self setBulle:nil];
    [self setNiveauBar:nil];
    [self setLabelXYZ:nil];
    [self setNiveauBar:nil];
    [self setBulle:nil];
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
    //if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
    //    return (interfaceOrientation == UIInterfaceOrientationLandscapeLeft || interfaceOrientation == UIInterfaceOrientationLandscapeRight);
    //} else {
        return YES;
    //}
     
}

-(void)configureAccelerometer
{
    UIAccelerometer*  theAccelerometer = [UIAccelerometer sharedAccelerometer];
    theAccelerometer.updateInterval = 1 / 25.;
    
    theAccelerometer.delegate = self;
}

- (void)accelerometer:(UIAccelerometer *)accelerometer didAccelerate:(UIAcceleration *)acceleration
{
    UIAccelerationValue x, y;
    float theta;
    x = acceleration.x;
    y = acceleration.y;
    
    if( fabsf(xprec - x) > 0.02 || fabsf(yprec - y) > 0.02) //Test pour enlever le bruit inutile
    {
        yprec = y;
        xprec = x;
        
        if(x > 0.)
            theta = atanf(-y/x) *180.0 /M_PI;
        else
            theta = ( (M_PI/2.)  + atanf(x/y)) * 180.0/M_PI;
        
        //[niveauBar.frame.size];
        [bulle setCenter:CGPointMake((-y + 1.0)*(niveauBar.frame.size.width/2 - bulle.frame.size.width/2) +20 + bulle.frame.size.width/2,[niveauBar center].y)];
        
        labelXYZ.text = [NSString stringWithFormat:@"angle =%2.2f °" ,theta, niveauBar.frame.size.width];

    }
}


- (void)dealloc {
    [bulle release];
    [niveauBar release];
    [labelXYZ release];
    [barreBulle release];
    [bulle release];
    [super dealloc];
}
@end
