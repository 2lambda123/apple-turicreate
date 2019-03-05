import React, { Component } from 'react';
import style from './index.module.scss';

import leftArrow from './assets/left_arrow.svg';
import rightArrow from './assets/right_arrow.svg';
import ImageLabeler from './ImageLabeler/index'

class SingleImage extends Component {

  componentDidMount() {
    this.props.getData(0, 1);
  }

  decrementIndex = () => {
    if (this.props.incrementalCurrentIndex > 0) {
      this.props.updateIncrementalCurrentIndex(this.props.incrementalCurrentIndex - 1);
      this.props.getData((this.props.incrementalCurrentIndex - 2), this.props.incrementalCurrentIndex);
    } else {
      // update error
      console.log("Update Error")
    }
  }

  incrementIndex = () => {
    if (this.props.incrementalCurrentIndex < (this.props.numElements - 1)) {
      this.props.updateIncrementalCurrentIndex(this.props.incrementalCurrentIndex + 1);
      this.props.getData(this.props.incrementalCurrentIndex, (this.props.incrementalCurrentIndex + 2));
    } else {
      // update error
      console.log("More Error")
    }
  }

  render() {
    return (
      <div className={style.SingleImage}>
        <div className={style.SingleImageContainer}>
            <div className={style.LeftArrow}
                 onClick={this.decrementIndex.bind(this)}>
                <img src={leftArrow} />
            </div>
            <ImageLabeler src={this.props.src}/>
            <div className={style.RightArrow}
                 onClick={this.incrementIndex.bind(this)}  >
                <img src={rightArrow} />
            </div>
        </div>
      </div>
    );
  }
}

export default SingleImage;