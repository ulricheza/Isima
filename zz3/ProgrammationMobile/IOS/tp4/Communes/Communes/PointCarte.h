//
//  PointCarte.h
//  Communes
//
//  Created by Maxime Escourbiac on 13/02/12.
//  Copyright (c) 2012 ISIMA. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MapKit/MapKit.h>

@interface PointCarte : NSObject<MKAnnotation> {
    NSString                *title_; 
    NSString                *subtitle_; 
    CLLocationCoordinate2D  coordinate_; 
}

@property (nonatomic) CLLocationCoordinate2D   coordinate; 
@property (nonatomic,copy) NSString                     *title; 

- (id)initWithCoordinate:(CLLocationCoordinate2D)c title:(NSString *)t; 

@end