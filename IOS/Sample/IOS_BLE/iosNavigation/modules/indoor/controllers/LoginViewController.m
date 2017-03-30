//
//  LoginViewController.m
//  iosNavigation
//
//  Created by AppleFace on 24.02.17.
//  Copyright © 2017 Ievgen. All rights reserved.
//

#import "LoginViewController.h"
#import "IndoorTableController.h"
#import "SessionManager.h"

@interface LoginViewController ()
@property (nonatomic, assign) NSInteger count;

@end

@implementation LoginViewController
- (void)viewDidLoad {
    [super viewDidLoad];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(didGetNotification)
                                                 name:@"login"
                                               object:nil];
        [[SessionManager sharedManager] loginToServer];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}
-(void)didGetNotification{
    self.count = 1;
    [self.navigationController showViewController:[self.storyboard instantiateViewControllerWithIdentifier:@"IndoorTableController"] sender:nil];

//[self.navigationController pushViewController:[self.storyboard instantiateViewControllerWithIdentifier:@"IndoorTableController"] animated:NO];
}
- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    
    
}

#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}


@end
