const mongoose = require('mongoose');
const bcrypt = require('bcrypt');
const saltRounds = 10;
const jwt = require('jsonwebtoken');


const userSchema = mongoose.Schema({
    name:{
        type: String,
        maxlength: 50
    },
    email: {
        type: String,
        trim: true, //! �����̽��� �����ִ� ȿ��
        unique: 1 //! �Ȱ����� ������.
    },
    password: {
        type: String,
        minlength: 5
    },
    lastname: {
        type: String,
        maxlength: 50
    },
    role: {
        type: Number,
        default: 0 //! �⺻���� 0�̰� ������, �Ϲ� ����ؼ� number�� ��������
    },
    image: String,
    token: {
        type: String
    },
    tokenExp:{
        type: Number
    }
})

userSchema.pre('save', function(next){
    var user = this;

    if(user.isModified('password')){
    //!��й�ȣ�� ��ȣȭ ��Ű��.
        bcrypt.genSalt(saltRounds, function(err, salt) {
            if(err) return next(err)

            bcrypt.hash(user.password, salt, function(err, hash) {
                if(err) return next(err)
                user.password = hash
                next()
                // Store hash in your password DB.
            })
        })
    } else {
        next()
    }
})

userSchema.methods.comparePassword = function(plainPassword, cb){
    //plainPassword 12345678      ��ȣȭ�� ��й�ȣ !@#!%$!@#!@#!@#!@#!@#
    bcrypt.compare(plainPassword, this.password, function(err, isMatch){
        if(err) return cb(err);
            cb(null, isMatch);
    })
}

userSchema.methods.generateToken = function(cb){
    var user = this;
    //!��ū �����ϱ�
    var token = jwt.sign(user._id.toHexString(), 'secretToken')

    // user._id + 'secretToken' = token
    user.token = token
    user.save(function(err, user){
        if(err) return cb(err)
        cb(null, user)
    })
}

userSchema.statics.findByToken = function(token, cb){
    var user = this;

    //! ��ū�� ���ڵ� �Ѵ�.
    jwt.verify(token, 'secretToken', function(err, decoded){
        //���� ���̵� �̿��ؼ� ������ ã�� ������ Ŭ���̾�Ʈ���� ������ ��ū�� DB�� ������ ��ū�� ��ġ�ϴ��� Ȯ��
        user.findOne({"_id": decoded, "token": token}, function(err, user){
        
            if(err) return cb(err);
            cb(null, user)
        })
    })

}



const User = mongoose.model('User', userSchema) //! ��Ű���� �𵨷� ���Ѵ�.

module.exports = { User }