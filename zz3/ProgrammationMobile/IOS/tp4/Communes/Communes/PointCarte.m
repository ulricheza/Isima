//
//  PointCarte.m
//  Communes
//
//  Created by Maxime Escourbiac on 13/02/12.
//  Copyright (c) 2012 ISIMA. All rights reserved.
//

#import "PointCarte.h"



@implementation PointCarte
@synthesize coordinate = _coordinate;
@synthesize title = _title;

-(id)initWithCoordinate:(CLLocationCoordinate2D)c title:(NSString *)t {
    _title = t;
    _coordinate = c;
    
    return self;
}

@end
