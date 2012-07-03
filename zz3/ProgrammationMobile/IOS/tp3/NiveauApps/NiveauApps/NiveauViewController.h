//
//  NiveauViewController.h
//  NiveauApps
//
//  Created by Maxime Escourbiac on 24/01/12.
//  Copyright (c) 2012 ISIMA. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface NiveauViewController : UIViewController<UIAccelerometerDelegate>
{
    UIAccelerationValue xprec;
    UIAccelerationValue yprec;
    float tailleBulle;
    float tailleFond;
    float centreFond;
    float distBord;
}

@property (retain, nonatomic) IBOutlet UIImageView *bulle;
@property (retain, nonatomic) IBOutlet UIImageView *fondBulle;
@property (retain, nonatomic) IBOutlet UILabel *labelAngle;
@property (retain, nonatomic) IBOutlet UILabel *labelAcc;

-(void)configureAccelerometer;

@end
