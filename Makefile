TARGET = skybreak

.PHONY: all clean

all: clean
	xcodebuild clean build CODE_SIGN_IDENTITY="" CODE_SIGNING_REQUIRED=NO PRODUCT_BUNDLE_IDENTIFIER="com.cryptic.skybreak841" -sdk iphoneos -configuration Release
	ln -sf build/Release-iphoneos Payload
	strip Payload/$(TARGET).app/$(TARGET)
	jtool --sign --inplace Payload/$(TARGET).app/$(TARGET)
	zip -rq9 $(TARGET).ipa Payload/$(TARGET).app

clean:
	rm -rf build Payload $(TARGET).ipa
