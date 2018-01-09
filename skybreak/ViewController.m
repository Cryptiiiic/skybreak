//
//  ViewController.m
//  skybreak
//
//  Created by Cryptic on 1/8/18.
//  Copyright © 2018 Cryptic. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()
@property (weak, nonatomic) IBOutlet UILabel *KSlide;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    unsigned long long kslide = get_kslide();
    NSString *text = [NSString stringWithFormat:@"0x%qX", kslide];
    _KSlide.text = text;
    // Do any additional setup after loading the view, typically from a nib.
}
    


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
