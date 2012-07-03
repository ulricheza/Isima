//
//  ViewController.h
//  NiveauProject
//
//  Created by Jean-Christophe SEPTIER on 1/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <math.h>


@interface ViewController : UIViewController<UIAccelerometerDelegate>
{
    UIAccelerationValue xprec;
    UIAccelerationValue yprec;
    float tailleBulle;
    float tailleBarre;
}

-(void)configureAccelerometer;

@property (retain, nonatomic) IBOutlet UILabel *labelXYZ;
@property (retain, nonatomic) IBOutlet UIImageView *niveauBar;
@property (retain, nonatomic) IBOutlet UIImageView *bulle;

@end
