//
//  ViewController.h
//  AppareilPhotoProject
//
//  Created by Jean-Christophe SEPTIER on 1/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MessageUI/MessageUI.h>
#import <MessageUI/MFMailComposeViewController.h>

@interface ViewController : UIViewController <UIImagePickerControllerDelegate,UINavigationControllerDelegate,MFMailComposeViewControllerDelegate>
{
    UIImagePickerController *imagePicker;
    UIImage *imageTake;
}

- (IBAction)MailPicture:(id)sender;

@property (retain, nonatomic) IBOutlet UIImage *imageTake;

@property (retain, nonatomic) IBOutlet UIImageView *ImagePicture;

@property (retain, nonatomic) IBOutlet UIButton *ButtonSendMail;

@property (retain, nonatomic) IBOutlet UIButton *ButtonTakePhoto;

@property (nonatomic, retain) UIImagePickerController *imagePicker;

@end
