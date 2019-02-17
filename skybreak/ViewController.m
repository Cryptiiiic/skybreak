//
//  ViewController.m
//  skybreak
//
//  Created by Cryptic on 1/8/18.
//  Copyright © 2019 Cryptic. All rights reserved.
//

#import "ViewController.h"
#include "exploit.h"

@interface ViewController ()
@property (weak, nonatomic) IBOutlet UILabel *KSlide;

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    NSString *text = [NSString stringWithFormat:@"0x%X", get_kslide()];
    _KSlide.text = text;
}
    


- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

@end
