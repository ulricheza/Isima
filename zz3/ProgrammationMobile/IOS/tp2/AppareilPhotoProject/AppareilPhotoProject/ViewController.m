//
//  ViewController.m
//  AppareilPhotoProject
//
//  Created by Jean-Christophe SEPTIER on 1/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "ViewController.h"

@implementation ViewController
@synthesize ImagePicture;
@synthesize ButtonSendMail;
@synthesize ButtonTakePhoto;
@synthesize imagePicker;
@synthesize imageTake;

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{   
    self.imagePicker = [[UIImagePickerController alloc] init];
    self.imagePicker.delegate = self;
    self.imagePicker.sourceType = UIImagePickerControllerSourceTypeCamera;
    [ButtonSendMail setEnabled:FALSE];
    [super viewDidLoad];   
    [self.imagePicker autorelease];

}
- (IBAction)TakePhoto:(id)sender {
	[self presentModalViewController:self.imagePicker animated:YES];
    
}

-(void)imagePickerControllerDidCancel:(UIImagePickerController *)picker
{
    [self dismissModalViewControllerAnimated:YES];
}

- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingImage:(UIImage *)img editingInfo:(NSDictionary *)editInfo
{
    imageTake = img;
	ImagePicture.image = img;
    [ButtonSendMail setEnabled:TRUE];
	[self dismissModalViewControllerAnimated:YES];
    
}

- (void)viewDidUnload
{
    [self setButtonTakePhoto:nil];
    [self setButtonSendMail:nil];
    [self setImagePicture:nil];
    [super viewDidUnload];
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
    return FALSE;
}

- (void)dealloc {
    [ButtonTakePhoto release];
    [ButtonSendMail release];
    [ImagePicture release];
    [super dealloc];
}

-(void)mailComposeController:(MFMailComposeViewController *)controller didFinishWithResult:(MFMailComposeResult)result error:(NSError *)error
{
     [self dismissModalViewControllerAnimated:YES];
}


- (IBAction)MailPicture:(id)sender {
    
    if(imageTake != nil)
    {
        MFMailComposeViewController *picker = [[MFMailComposeViewController alloc] init];
    
        picker.mailComposeDelegate = self;
        [picker setSubject:@"Regarde la photo que je viens de faire avec PriseDeVue"];
    
        NSData *imageData = UIImageJPEGRepresentation(imageTake, 1);
        [picker addAttachmentData:imageData mimeType:@"image/jpg" fileName:@"RobotWithPencil.jpg"];
   
        //Récupérer la date
        NSDate* date = [NSDate date];
        NSDateFormatter* formatter = [[[NSDateFormatter alloc] init] autorelease];
        [formatter setDateFormat:@"dd-MM-yyyy"];
        NSString* str = [formatter stringFromDate:date];
    
        NSString *emailBody = [NSString stringWithFormat:@"Regarde la photo que je viens de faire avec PriseDeVue. Prise le %@", str] ;
        [picker setMessageBody:emailBody isHTML:YES];
        [self presentModalViewController:picker animated:YES];
    }
}
@end
