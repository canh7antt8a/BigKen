#import <UIKit/UIKit.h>

@class RootViewController;

@interface AppController : NSObject <UIApplicationDelegate> {
    UIWindow *window;
    std::string facebookId;
    std::string accessToken;
    std::string facebookName;
}

- (std::string) loginAction:(int)index;
- (std::string) getAccessToken;
- (std::string) getUserId;
- (std::string) getUserName;

@property(nonatomic, readonly) RootViewController* viewController;

@end

