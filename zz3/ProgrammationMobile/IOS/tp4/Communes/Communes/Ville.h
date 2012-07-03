//
//  Ville.h
//  Communes
//
//  Created by Maxime Escourbiac on 07/02/12.
//  Copyright (c) 2012 ISIMA. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Ville : NSObject {

}

@property (strong, nonatomic) NSString * nom;
@property (strong, nonatomic) NSString * nomMAJ;
@property (strong, nonatomic) NSString * codePostal;
@property (strong, nonatomic) NSString * codeInsee;
@property (strong, nonatomic) NSString * codeRegion;
@property float latitude;
@property float longitude;
@property float distance;

@end

