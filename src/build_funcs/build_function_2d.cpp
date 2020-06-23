void 												
World::Build(void) {
    vp_.SetHRes(512);
	vp_.SetVRes(512);
	vp_.SetPixelSize(0.040);
    vp_.SetSamples(16);
	vp_.SetGamma(1.0);
	
	background_color_ = kWhite;
	tracer_ptr_ = new Function2D(this); 
}
