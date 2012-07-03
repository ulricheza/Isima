//
//  NiveauViewController.m
//  NiveauApps
//
//  Created by Maxime Escourbiac on 24/01/12.
//  Copyright (c) 2012 ISIMA. All rights reserved.
//

#import "NiveauViewController.h"

@implementation NiveauViewController
@synthesize bulle;
@synthesize fondBulle;
@synthesize labelAngle;
@synthesize labelAcc;

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
    tailleBulle = bulle.frame.size.width/2;
    tailleFond = fondBulle.frame.size.width/2;
    centreFond = [fondBulle center].y;
    distBord = [fondBulle center].x - tailleFond;
    xprec = 0.;
    yprec = 0.;
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)viewDidUnload
{
    [self setBulle:nil];
    [self setFondBulle:nil];
    [self setLabelAngle:nil];
    [self setLabelAcc:nil];
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
    return YES;
}

- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation
{
    tailleBulle = bulle.frame.size.width/2;
    tailleFond = fondBulle.frame.size.width/2;
    centreFond = [fondBulle center].y;
    distBord = ([fondBulle center].x - tailleFond);
}
     
- (void)dealloc {
    [bulle release];
    [fondBulle release];
    [labelAngle release];
    [labelAcc release];
    [super dealloc];
}

-(void)configureAccelerometer
{
    UIAccelerometer*  theAccelerometer = [UIAccelerometer sharedAccelerometer];
    theAccelerometer.updateInterval = 1 / 25.;
    theAccelerometer.delegate = self;
}

- (void)accelerometer:(UIAccelerometer *)accelerometer didAccelerate:(UIAcceleration *)acceleration
{
    UIAccelerationValue x, y, z;
    float theta;
    x = acceleration.x;
    y = acceleration.y;
    z = acceleration.z;
    
    if( fabsf(xprec - x) > 0.02 || fabsf(yprec - y) > 0.02) //Test pour enlever le bruit inutile
    {
        yprec = y;
        xprec = x;
        
        switch([self interfaceOrientation])
        {
            case UIInterfaceOrientationPortrait :
                [bulle setCenter:CGPointMake((-x + 1.0)*(tailleFond - tailleBulle ) + distBord + tailleBulle,centreFond)];
                theta = atanf(x/y) *180.0 /M_PI;
                break;
            case UIInterfaceOrientationPortraitUpsideDown :
                [bulle setCenter:CGPointMake((x + 1.0)*(tailleFond - tailleBulle ) + distBord + tailleBulle,centreFond)];
                theta = atanf(x/y) *180.0 /M_PI;
                break;
            case UIInterfaceOrientationLandscapeLeft :
                [bulle setCenter:CGPointMake((-y + 1.0)*(tailleFond - tailleBulle ) + distBord + tailleBulle,centreFond)];
                theta = -atanf(y/x) *180.0 /M_PI;
                break;
            case UIInterfaceOrientationLandscapeRight :
                [bulle setCenter:CGPointMake((y + 1.0)*(tailleFond - tailleBulle ) +distBord + tailleBulle,centreFond)];
                theta = -atanf(y/x) *180.0 /M_PI;
                break;
        }
        
        labelAngle.text = [NSString stringWithFormat:@"angle =%2.2f °" ,theta];
        labelAcc.text = [NSString stringWithFormat:@"x =%2.2f, y =%2.2f, z =%2.2f " ,x,y,z];
    }
}


@end
