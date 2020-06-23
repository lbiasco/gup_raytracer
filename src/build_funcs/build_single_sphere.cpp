void 												
World::Build(void) {
    vp_.SetHRes(200);
	vp_.SetVRes(200);
	vp_.SetPixelSize(1.0);
    vp_.SetSamples(16);
	vp_.SetGamma(1.0);
	
	background_color_ = kWhite;
	tracer_ptr_ = new SingleSphere(this); 
	
	sphere_.SetCenter(0.0);
	sphere_.SetRadius(85);
}
