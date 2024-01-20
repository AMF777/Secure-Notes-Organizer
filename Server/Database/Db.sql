use SecureNoteOrganizer;
-- Create users table
drop table if exists users;
CREATE TABLE users (
    user_id int auto_increment PRIMARY KEY,
    username VARCHAR(255) NOT NULL,
    email VARCHAR(255) UNIQUE NOT NULL,
    password_hash VARCHAR(255) NOT NULL
);

-- Create notes table
drop table if exists notes;
CREATE TABLE notes (
    note_id int auto_increment  PRIMARY KEY,
    user_id INTEGER REFERENCES users(user_id),
    title VARCHAR(255),
    created_at TIMESTAMP,
    updated_at TIMESTAMP
);

-- Create tags table
drop table if exists tags;
CREATE TABLE tags (
    tag_id int auto_increment  PRIMARY KEY,
    tag_name VARCHAR(255)  NOT NULL
);

-- Create note_tags table
drop table if exists note_tags;
CREATE TABLE note_tags (
    note_id INTEGER REFERENCES notes(note_id),
    tag_id INTEGER REFERENCES tags(tag_id),
    PRIMARY KEY (note_id, tag_id)
);

-- Create note_shares table
drop table if exists note_shares;
CREATE TABLE note_shares (
    share_id int auto_increment  PRIMARY KEY,
    note_id INTEGER REFERENCES notes(note_id),
    shared_by_user_id INTEGER REFERENCES users(user_id),
    shared_with_user_id INTEGER REFERENCES users(user_id)
);

-- Create Component_note table
drop table if exists Component_note;
CREATE TABLE Component_note (
    Component_id int auto_increment  PRIMARY KEY,
    note_id INTEGER REFERENCES notes(note_id),
    Component_content TEXT,
    Font_size INTEGER,
    Font_color TEXT,
    Background_color TEXT,
    Font_family TEXT,
    Font_style TEXT,
    Font_bold BOOLEAN,
    Font_italic BOOLEAN,
    Font_underlined BOOLEAN
);
SHOW FULL COLUMNS From note_shares;
SHOW FULL COLUMNS From users;


-- Add foreign key constraints
 ALTER TABLE note_shares ADD CONSTRAINT fk_shared_by_user FOREIGN KEY (shared_by_user_id) REFERENCES users(user_id);
 ALTER TABLE note_shares ADD CONSTRAINT fk_shared_with_user FOREIGN KEY (shared_with_user_id) REFERENCES users(user_id);

-- Add foreign key constraints for note_tags
 ALTER TABLE note_tags ADD CONSTRAINT fk_note_tags_note FOREIGN KEY (note_id) REFERENCES notes(note_id);
 ALTER TABLE note_tags ADD CONSTRAINT fk_note_tags_tag FOREIGN KEY (tag_id) REFERENCES tags(tag_id);

-- Add foreign key constraint for Component_note
 ALTER TABLE Component_note ADD CONSTRAINT fk_Component_note_note FOREIGN KEY (note_id) REFERENCES notes(note_id);
