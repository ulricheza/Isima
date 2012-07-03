//
//  HelloWorldViewController.m
//  HelloTouchWorld
//
//  Created by Maxime ESCOURBIAC on 1/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "HelloWorldViewController.h"


@implementation HelloWorldViewController
@synthesize labelText;
@synthesize buttonTirage;

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    tirage = [[Tirage alloc] init];
}

- (void)viewDidUnload
{
    [self setLabelText:nil];
    [self setButtonTirage:nil];
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

// Méthode appelée lorsque l'on clique sur le bouton tirage
- (IBAction)clickTirage:(id)sender {
	
    int val;
    NSMutableString *text = [[[NSMutableString alloc] init] retain];    
    
	// Affichage des 5 numéros
    for (int i = 0; i<5; ++i)
    {
        val = [tirage generateInt];
        [text appendString: [NSString stringWithFormat:@" %i", val]];
    }
    
	// Affichage du complémentaire
    val = [tirage generateIntComp];
    
    [text appendString: @" Numéro Complémentaire"];
    [text appendString: [NSString stringWithFormat:@" %i", val]];
    
	// Affiche le texte dans notre label
    [labelText setText:text];
    
    [text autorelease];
}

// Libération de la mémoire
- (void)dealloc {
    [labelText release];
    [buttonTirage release];
    [tirage dealloc];
    [super dealloc];
}
@end
