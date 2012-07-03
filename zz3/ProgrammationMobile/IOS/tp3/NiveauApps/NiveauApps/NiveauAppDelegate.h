//
//  NiveauAppDelegate.h
//  NiveauApps
//
//  Created by Maxime Escourbiac on 24/01/12.
//  Copyright (c) 2012 ISIMA. All rights reserved.
//

#import <UIKit/UIKit.h>

@class NiveauViewController;

@interface NiveauAppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;

@property (strong, nonatomic) NiveauViewController *viewController;

@end
